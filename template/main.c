#include "../utils.h"

#define LINE_LENGTH 64

void part1(char* input) {
    char* arr[8] = {0};
    int i = 0, res = 0;
    str_split(arr, input, "\n\n");
    while (arr[i] != NULL) str_rep_all(arr[i++], '\n', ' ');

    /////////////
    printf("\nPart 1: %d\n", res);
}

void part2(char* input) {
    char* arr[8] = {0};
    int i = 0, res = 0;
    str_split(arr, input, "\n\n");
    while (arr[i] != NULL) str_rep_all(arr[i++], '\n', ' ');

    /////////////
    printf("\nPart 2: %d\n", res);
}

int main(int argc, char** argv) {
    char* input = load_file(argc, argv);

    TIMER(part1, input);
    TIMER(part2, input);
}
