#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t fnv1a(const char* key) {
    uint64_t hash = 0xcbf29ce484222325ULL;  // FNV offset basis
    int i = 0;
    while (key[i] != '\0') {
        hash ^= (unsigned char)key[i++];  // xor FIRST (that's the "a" variant)
        hash *= 0x100000001b3ULL;         // FNV prime
    }
    return hash;
}

typedef struct {
    int value;
    char* key;
} Entry;

typedef struct {
    size_t capacity;
    size_t count;
    Entry* entries;
} HashMap;

void hm_set(HashMap* hm, char* k, int v) {
    hm->entries[fnv1a(k) % hm->capacity] = (Entry){v, k};
    hm->count++;
}

int hm_get(HashMap* hm, char* k) { return hm->entries[fnv1a(k) % hm->capacity].value; }

HashMap* hm_new(size_t cap) {
    return *(HashMap) {
    capacity:
        cap, count : 0, entries : malloc(sizeof(int) * cap)
    }
}

int main(void) {
    char* key = "abcd";

    int* hashmap = malloc(1024);

    hashmap[fnv1a("test1") % 1024] = 12;
    hashmap[fnv1a("test2") % 1024] = 13;

    printf("test1: %d\n", hashmap[fnv1a("test1") % 1024]);
    printf("test2: %d\n", hashmap[fnv1a("test2") % 1024]);
}