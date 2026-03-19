#ifndef NOLB_H
#define NOLB_H

#include <ctype.h>
#include <curl/curl.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define TOKEN_PATH ".env"

#define log_info(m, ...) printf("[INFO]\t" m "\n", ##__VA_ARGS__)
#define log_error(m, ...) printf("[ERROR]\t" m "\n", ##__VA_ARGS__)

typedef struct {
    const char** items;
    size_t count;
    size_t capacity;
} Nolb_Cmd;

typedef struct {
    char* day;
    bool test;
    bool debug;
} Nolb_Args;

#define a_append(xs, x)                                                                \
    do {                                                                               \
        if ((xs)->count >= (xs)->capacity) {                                           \
            if ((xs)->capacity == 0)                                                   \
                (xs)->capacity = 256;                                                  \
            else                                                                       \
                (xs)->capacity *= 2;                                                   \
            (xs)->items = realloc((xs)->items, (xs)->capacity * sizeof(*(xs)->items)); \
        }                                                                              \
        (xs)->items[(xs)->count++] = x;                                                \
    } while (0)

#define cmd_append(xs, ...)                                                     \
    do {                                                                        \
        __typeof__((xs)->items[0]) _vals[] = {__VA_ARGS__};                     \
        size_t _n = sizeof(_vals) / sizeof(_vals[0]);                           \
        if ((xs)->count + _n >= (xs)->capacity) {                               \
            size_t new_cap = ((xs)->capacity == 0) ? _n : (xs)->capacity;       \
            while (new_cap < (xs)->count + _n) new_cap *= 2;                    \
            (xs)->items = realloc((xs)->items, new_cap * sizeof(*(xs)->items)); \
            (xs)->capacity = new_cap;                                           \
        }                                                                       \
        memcpy((xs)->items + (xs)->count, _vals, sizeof(_vals));                \
        (xs)->count += _n;                                                      \
    } while (0)

// int nolb_rebuild_if_needed(int argc, char** argv) {
//     const char* filename = __FILE__;
//     struct stat file_stats;
//     // stat() returns 0 on success
//     if (stat(filename, &file_stats) == -1) {
//         perror("Error getting file stats");
//         return EXIT_FAILURE;
//     }
//     // ctime() is the traditional way; it includes a newline
//     printf("File: %s\n", filename);
//     printf("Last modification (mtime): %s", ctime(&file_stats.st_mtime));
//     printf("Last status change (ctime): %s", ctime(&file_stats.st_ctime));
// }

char* get_token(void) {
    log_info("Retrieving token...");
    FILE* fp = fopen(TOKEN_PATH, "r");
    if (fp == nullptr) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    static char token[512] = {0};
    char line[512] = {0};
    if (fgets(line, sizeof(line), fp) != nullptr) {
        char* eq = strchr(line, '=');
        if (eq != nullptr) {
            strncpy(token, eq + 1, sizeof(token) - 1);
            token[strcspn(token, "\n")] = '\0';
        }
    }
    fclose(fp);
    log_info("Token retrieved!");

    return token;
}

char* construct_string(char* t, char* r) {
    int len = snprintf(nullptr, 0, t, r) + 1;
    char* res = malloc((size_t)len);
    if (!res) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    snprintf(res, len, t, r);
    return res;
}

int fetch_and_write_input(Nolb_Args* nargs) {
    log_info("Fetching input...");

    CURL* curl;

    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK) return (int)result;

    curl = curl_easy_init();
    if (curl) {
        char* token = get_token();

        char* path = construct_string("%s/input.txt", nargs->day);
        char* url = construct_string("https://adventofcode.com/2020/day/%s/input", nargs->day);
        char* cookie = construct_string("Cookie: session=%s", token);

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, cookie);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        FILE* fp = fopen(path, "w+");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        result = curl_easy_perform(curl);
        if (result != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    log_info("Input fetched!");

    return (int)result;
}

int create_main_and_test(Nolb_Args* nargs) {
    if (nargs->day == nullptr) return 0;
    char sc[] = {
#embed "template/main.c" suffix(, 0)
    };

    char* path = construct_string("%s/main.c", nargs->day);
    FILE* fp = fopen(path, "w+");
    fwrite(sc, strlen(sc), 1, fp);
    fclose(fp);

    char* testpath = construct_string("%s/test.txt", nargs->day);
    FILE* fpt = fopen(testpath, "w+");
    fclose(fpt);

    return 0;
}

int folder_already_exists(Nolb_Args* nargs) {
    struct stat sb;
    return (stat(nargs->day, &sb) == 0 && S_ISDIR(sb.st_mode));
}
int scaffold(Nolb_Args* nargs) {
    log_info("Scaffolding...");
    if (mkdir(nargs->day, 0755) == 0) {
        log_info("Folder created");
        fetch_and_write_input(nargs);
        return create_main_and_test(nargs);
    } else {
        perror("mkdir");
        log_error("Wtf??");
        exit(EXIT_FAILURE);
    }
}

int scaffold_if_needed(Nolb_Args* nargs) {
    if (!folder_already_exists(nargs)) return scaffold(nargs);
    return 0;
}

bool run_cmd(Nolb_Cmd* cmd) {
    cmd_append(cmd, nullptr);

    pid_t pid = fork();
    if (pid < 0) {
        log_error("Fork went wrong: %d", pid);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // child
        execvp((char* const)(cmd->items[0]), (char* const*)(cmd->items));
        char se[1024] = {0};
        strcat(se, strerror(errno));
        strcat(se, " (does \"%s\" exists?)");

        log_error("%s", construct_string(se, (char* const)cmd->items[0]));
        exit(EXIT_FAILURE);
    }

    // Parent process: wait for child to finish
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) printf("Command exited with code: %d\n", WEXITSTATUS(status));

    return true;
}

#endif