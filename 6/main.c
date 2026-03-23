#include "../utils.h"

#define ARRAY_LENGTH 4096

void part1(char* arr[ARRAY_LENGTH]) {
    int i = 0, res = 0, cmap[128] = {0}, grpcmap[128] = {0};
    char* ptr;
    while (arr[i] != NULL) {
        ptr = &arr[i][0];
        while (*ptr != '\0') {
            grpcmap[*ptr]++;
            ptr++;
        }
        for (int k = 97; k < 124; ++k) {
            cmap[k] += grpcmap[k] > 0;
            grpcmap[k] = 0;
        }
        i++;
    }
    for (int k = 97; k < 124; ++k) {
        res += cmap[k];
    }
    /////////////
    printf("\nPart 1: %d\n", res);
}

void part2(char* arr[ARRAY_LENGTH]) {
    int i = 0, res = 0, cmap[128] = {0}, grpcmap[128] = {0};
    char* ptr;
    while (arr[i] != NULL) {
        ptr = &arr[i][0];
        int person = 1;
        while (*ptr != '\0') {
            int subgrpcmap[128] = {0};
            // while(*ptr != '\n') {
            //     subgrpcmap

            // }
            if (*ptr == '\n') person++;
            grpcmap[*ptr]++;
            ptr++;
        }
        for (int k = 97; k < 124; ++k) {
            cmap[k] += grpcmap[k] == person;
            grpcmap[k] = 0;
        }
        i++;
    }
    for (int k = 97; k < 124; ++k) {
        res += cmap[k];
    }
    /////////////
    printf("\nPart 2: %d\n", res);
}

int main(int argc, char** argv) {
    char* input = load_file(argc, argv);
    char* arr[ARRAY_LENGTH] = {0};
    cstr_split(arr, input, "\n\n");

    TIMER(part1, arr);
    TIMER(part2, arr);
}
