#define _POSIX_C_SOURCE 199309L

#include "../utils.h"

void part1(FILE* fp) {
    char line[1024];
    int arr[1024] = {0};
    int el = 0, i = 0;
    while (fgets(line, 1024, fp) != nullptr) {
        sscanf(line, "%d", &el);
        arr[i++] = el;
    }
    for (int i = 0; i < 1024; i++) {
        for (int j = i; j < 1024; j++) {
            if (arr[i] + arr[j] == 2020) {
                printf("Part 1: %d\n", arr[i] * arr[j]);
                goto loopEnd;
            }
        }
    }
loopEnd:
}

void part2(FILE* fp) {
    char line[1024];
    int arr[1024] = {0};
    int el = 0, i = 0;
    while (fgets(line, 1024, fp) != nullptr) {
        sscanf(line, "%d", &el);
        arr[i++] = el;
    }
    for (int i = 0; i < 1024; i++) {
        if (!arr[i]) continue;
        for (int j = i; j < 1024; j++) {
            if (!arr[j]) continue;
            for (int k = j; k < 1024; k++) {
                if (!arr[k]) continue;
                if (arr[i] + arr[j] + arr[k] == 2020) {
                    printf("Part 2: %d\n", arr[i] * arr[j] * arr[k]);
                    goto loopEnd;
                }
            }
        }
    }
loopEnd:
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
