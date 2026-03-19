#define _GNU_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct {
    FILE* handle;
    long n_chars;
    int n_lines;
    char* content;
} File_Object;

File_Object get_file(char* path) {
    File_Object fo = {0};
    FILE* f = fopen(path, "r");
    if (f == nullptr) {
        perror("fopen");
        return fo;
    }
    fo.handle = f;
    fseek(fo.handle, 0, SEEK_END);
    fo.n_chars = ftell(fo.handle);
    fseek(fo.handle, 0, SEEK_SET);

    return fo;
}

void load_content(File_Object* f) {
    char* c = (char*)malloc(sizeof(char) * f->n_chars + 1);
    fread(c, 1, f->n_chars, f->handle);
    f->content = c;
}

int get_n_of_lines(FILE* f) {
    fseek(f, 0, SEEK_SET);
    int c;
    int nol = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') nol++;
    }
    return nol;
}