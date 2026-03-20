#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// byr (Birth Year) - four digits; at least 1920 and at most 2002.
bool byr(char* in) {
    if (strlen(in) != 4) return false;
    int i = 0;
    while (in[i] != 0)
        if (!isdigit(in[i++])) return false;
    int x = atoi(in);
    if (x < 1920 || x > 2002) return false;

    return true;
}
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
bool iyr(char* in) {
    if (strlen(in) != 4) return false;
    int x = atoi(in);
    if (x < 2010 || x > 2020) return false;

    return true;
}
// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
bool eyr(char* in) {
    if (strlen(in) != 4) return false;
    int x = atoi(in);
    if (x < 2020 || x > 2030) return false;

    return true;
}
// hgt (Height) - a number followed by either cm or in:
//     If cm, the number must be at least 150 and at most 193.
//     If in, the number must be at least 59 and at most 76.
bool hgt(char* in) {
    bool is_cm = strstr(in, "cm") != NULL;
    bool is_in = strstr(in, "in") != NULL;

    if (!(is_cm || is_in)) return false;

    int v = atoi(in);
    if (is_cm && (v < 150 || v > 193)) return false;
    if (is_in && (v < 59 || v > 76)) return false;

    return true;
}
// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
bool hcl(char* in) {
    if (strlen(in) != 7) return false;
    if (in[0] != '#') return false;
    int i = 0;
    in++;
    while (in[i] != 0)
        if (!isalnum(in[i++])) return false;

    return true;
}
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
bool ecl(char* in) {
    char* valids[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth", NULL};
    int i = 0;
    while (valids[i] != NULL)
        if (strcmp(in, valids[i++]) == 0) return true;
    return false;
}
// pid (Passport ID) - a nine-digit number, including leading zeroes.
bool pid(char* in) {
    if (strlen(in) != 9) return false;
    int i = 0;
    while (in[i] != 0)
        if (!isdigit(in[i++])) return false;

    return true;
}