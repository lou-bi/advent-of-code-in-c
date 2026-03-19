#define _POSIX_C_SOURCE 199309L

#include "../utils.h"

#define LINE_LENGTH 64

void part1(FILE* fp) {
    int res = 0;
    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), fp) != nullptr) {
        int min, max;
        char tc;
        char s[LINE_LENGTH];
        sscanf(line, "%d-%d %c: %s", &min, &max, &tc, s);

        int i = 0, occ = 0;
        while (s[i] != '\0') {
            if (s[i] == tc) occ++;
            i++;
        }
        if (occ >= min && occ <= max) res++;
    }
    printf("Part 1: %d\n", res);
}

void part2(FILE* fp) {
    int res = 0;
    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), fp) != nullptr) {
        int min, max;
        char tc;
        char s[LINE_LENGTH];
        sscanf(line, "%d-%d %c: %s", &min, &max, &tc, s);
        min--;
        max--;
        if ((s[min] == tc && !(s[max] == tc)) || (!(s[min] == tc) && (s[max] == tc))) res++;
    }
    printf("Part 2: %d\n", res);
}

int main(int argc, char** argv) {
    const char* path = "input.txt";
    if (argc == 2 && strcmp(argv[1], "test") == 0) path = "test.txt";

    FILE* fp = fopen(path, "r");
    if (fp == nullptr) {
        printf("File does not exists: %s\n", path);
        exit(EXIT_FAILURE);
    }

    printf("\n");
    TIMER(part1, fp);
    printf("\n");
    fseek(fp, 0, SEEK_SET);
    TIMER(part2, fp);
    printf("\n");
}
