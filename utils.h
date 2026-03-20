#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define TIMER(fn, ...)                                                                                               \
    do {                                                                                                             \
        struct timespec a, b;                                                                                        \
        clock_gettime(CLOCK_MONOTONIC, &a);                                                                          \
        (fn)(__VA_ARGS__);                                                                                           \
        clock_gettime(CLOCK_MONOTONIC, &b);                                                                          \
        long double t = (long double)((b.tv_sec - a.tv_sec) * 1'000'000'000L + (b.tv_nsec - a.tv_nsec)) / 1'000'000; \
        printf("  took %Lf ms\n", t);                                                                                \
    } while (0)

FILE* get_file(int argc, char** argv) {
    const char* path = "input.txt";
    if (argc == 2 && strcmp(argv[1], "test") == 0) path = "test.txt";
    FILE* fp = fopen(path, "r+");
    return fp;
}

char* load_file(int argc, char** argv) {
    const char* path = "input.txt";
    if (argc == 2 && strcmp(argv[1], "test") == 0) path = "test.txt";

    struct stat st;
    if (stat(path, &st) != 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    off_t len = st.st_size;
    char* s = malloc(len);
    if (s == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    FILE* fp = fopen(path, "r+");
    if (fread(s, 1, len, fp) == 0) perror("fread");

    // trim right
    char* ptr = s + len - 1;
    while (isspace(*ptr)) {
        *ptr = '\0';
        ptr--;
    }

    // trim left
    while (isspace(*s)) s++;

    return s;
}

void cstr_split(char* buff[], char* in, char* sep) {
    char* start = in;
    char* found;
    int seplen = strlen(sep);

    int i = 0;
    while ((found = strstr(start, sep)) != NULL) {
        buff[i++] = start;
        *found = 0;
        start = found + seplen;
    }
    buff[i++] = start;
    buff[i] = NULL;
}
void cstr_split_any(char* buff[], char* in, char* sep) {
    char* start = in;
    char* found;

    int i = 0;
    while ((found = strpbrk(start, sep)) != NULL) {
        buff[i++] = start;
        *found = 0;
        start = found + 1;
    }
    buff[i++] = start;
    buff[i] = NULL;
}

void cstr_rep(char* s, char rep, char with) {
    char* found = strchr(s, rep);
    *found = with;
}

void cstr_rep_all(char* s, char rep, char with) {
    char* start = s;
    char* found;
    while ((found = strchr(start, rep)) != NULL) {
        *found = with;
        start = found;
    }
}