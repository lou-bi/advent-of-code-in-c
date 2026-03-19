#define _POSIX_C_SOURCE 199309L

#include "../utils.h"

#define LINE_LENGTH 64

void part1(FILE* fp) {
    int res = 0;
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != nullptr) {
        /////////////
    }
    printf("\nPart 1: %d\n", res);
}

void part2(FILE* fp) {
    int res = 0;
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, fp) != nullptr) {
        /////////////
    }
    printf("\nPart 2: %d\n", res);
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
    fseek(fp, 0, SEEK_SET);
    TIMER(part2, fp);
}
