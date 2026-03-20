#include "../utils.h"

#define LINE_LENGTH 64

typedef struct {
    int min;
    int max;
    int count;
    int seats[1024];
} Seats;

void part1(FILE* fp, Seats* s) {
    char line[12];
    int i = 0;
    while (fgets(line, 12, fp)) {
        int a = 0;
        char* p = &line[0];
        while (*p != '\n') {
            a <<= 1;
            if (*p == 'B' || *p == 'R') a |= 1;
            p++;
        }
        if (s->max < a) s->max = a;
        if (s->min > a) s->min = a;
        s->seats[i++] = a;
        s->count++;
    }

    /////////////
    printf("\nPart 1: %d\n", s->max);
}

void part2(FILE* fp, Seats* s) {
    int sum = 0, sum_seats = 0;
    for (int i = 0; i < s->count; i++) sum_seats ^= s->seats[i];
    for (int i = s->min; i <= s->max; i++) sum ^= i;

    int res = sum ^ sum_seats;
    /////////////
    printf("\nPart 2: %d\n", res);
}

int main(int argc, char** argv) {
    FILE* fp = get_file(argc, argv);
    Seats s = {.min = 1000, .max = 0};
    TIMER(part1, fp, &s);
    rewind(fp);
    TIMER(part2, fp, &s);
}
