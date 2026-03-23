#include "../utils.h"

#define LINE_LENGTH 64

typedef struct {
    char* color;
    Bag* containBags[16];
    int* containQuantity[16];
} Bag;

void part1(FILE* fp) {
    int res = 0;

    /////////////
    printf("\nPart 1: %d\n", res);
}

void part2(FILE* fp) {
    int res = 0;

    /////////////
    printf("\nPart 2: %d\n", res);
}

int main(int argc, char** argv) {
    char* fp = get_file(argc, argv);

    TIMER(part1, fp);
    TIMER(part2, fp);
}
