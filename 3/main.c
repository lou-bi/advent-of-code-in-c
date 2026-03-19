#define _POSIX_C_SOURCE 199309L

#include "../utils.h"

#define LINE_LENGTH 64

long long resolve(FILE* fp, int rx, int ry) {
    rewind(fp);
    long long res = 0LL;
    char line[LINE_LENGTH];
    int x = rx;
    for (int i = 0; i < ry; ++i) fgets(line, LINE_LENGTH, fp);
    line[strcspn(line, "\n")] = '\0';
    const int len = strlen(line);
    while (fgets(line, LINE_LENGTH, fp) != nullptr) {
        if (line[x] == '#') res++;
        x = (x + rx) % len;
        for (int i = 1; i < ry; ++i) fgets(line, LINE_LENGTH, fp);
    }
    printf("%d, %d: %lld\n", rx, ry, res);
    return res;
}

void part1(FILE* fp) { printf("\nPart 1: %lld\n", resolve(fp, 3, 1)); }

void part2(FILE* fp) {
    long long res = 1LL;
    res *= resolve(fp, 1, 1);
    res *= resolve(fp, 3, 1);
    res *= resolve(fp, 5, 1);
    res *= resolve(fp, 7, 1);
    res *= resolve(fp, 1, 2);
    printf("\nPart 2: %lld\n", res);
}

int main(int argc, char** argv) {
    const char* path = "input.txt";
    if (argc == 2 && strcmp(argv[1], "test") == 0) path = "test.txt";
    FILE* fp = fopen(path, "r");
    if (fp == nullptr) {
        printf("File does not exists: %s\n", path);
        exit(EXIT_FAILURE);
    }

    TIMER(part1, fp);
    TIMER(part2, fp);
}
