#include "../utils.h"

#define LINE_LENGTH 64

void part1(char* input) {
    char* arr[1024] = {0};
    int i = 0, res = 0;
    str_split(arr, input, "\n\n");

    char* tofind[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", NULL};

    while (arr[i] != NULL) {
        bool ok = true;
        int j = 0;
        while (tofind[j] != NULL) {
            if (strstr(arr[i], tofind[j]) == NULL) {
                ok = false;
                break;
            }
            j++;
        }
        if (ok) res++;

        i++;
    }

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
