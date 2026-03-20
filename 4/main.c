#include "../utils.h"
#include "verifs.h"

#define ARRAY_LENGTH 1064

void part1(char* arr[ARRAY_LENGTH]) {
    int i = 0, res = 0;

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
    printf("Part 1: %d\n", res);
}

void part2(char* arr[ARRAY_LENGTH]) {
    int i = 0, res = 0;

    char* els[ARRAY_LENGTH][9];
    while (arr[i] != NULL) {
        cstr_split_any(els[i], arr[i], " \n");
        i++;
    }
    els[i][0] = NULL;
    i = 0;

    char* tofind[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", NULL};
    bool (*verifs[])(char*) = {byr, iyr, eyr, hgt, hcl, ecl, pid};

loopPassport:
    while (els[i][0] != NULL) {
        bool is_ok = false;
        int k = 0;
        while (tofind[k] != NULL) {
            int j = 0;
            bool found = false;
            while (els[i][j] != NULL) {
                if ((strstr(els[i][j], tofind[k]) != NULL)) {
                    // found!
                    found = true;
                    char* ptr = strchr(els[i][j], ':') + 1;
                    is_ok = verifs[k](ptr);
                    if (!is_ok) {
                        i++;
                        goto loopPassport;
                    };
                    break;
                }
                j++;
            }
            if (!found) {
                i++;
                goto loopPassport;
            }
            k++;
        }
        if (is_ok) res++;
        i++;
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
