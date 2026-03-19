#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_split(char* in, char sep, char** res) {
    // int max = sizeof(res) / sizeof(res[0]);
    int i = 0;
    char c = 0;

    char* start = in;
    while ((c = *in) != '\0') {
        if (c == sep) {
            *in = '\0';
            res[i] = start;
            i++;
            start = in + 1;
        }
        in++;
    }
    *in = '\0';
    res[i] = start;
}

int main(void) {
    char* input = strdup("asd,wer,aer,ee");

    char* res[4];
    str_split(input, ',', res);

    printf("%s\n", res[0]);

    for (int i = 0; i < 4; i++) {
        printf("&res[%d] = %p  |  res[%d] = %p  |  value = \"%s\"\n", i,
               (void*)&res[i],    // address of the pointer itself
               i, (void*)res[i],  // address the pointer holds (where the string lives)
               res[i]);           // the actual string
    }
    printf("--------\n");
    char* ptr = input;
    for (int i = 0; i < 15; i++) {
        printf("%p -> '%c'\n", (void*)(ptr + i),
               ptr[i] ? ptr[i] : '.');  // print '.' for '\0'
    }
}

char* __strsep(char** stringp, const char* delim) {
    char *begin, *end;

    begin = *stringp;
    if (begin == NULL) return NULL;

    /* Find the end of the token.  */
    end = begin + strcspn(begin, delim);

    if (*end) {
        /* Terminate the token and set *STRINGP past NUL character.  */
        *end++ = '\0';
        *stringp = end;
    } else
        /* No more delimiters; this is the last token.  */
        *stringp = NULL;

    return begin;
}
