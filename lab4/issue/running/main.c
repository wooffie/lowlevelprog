#include <stddef.h>
#include <stdio.h>
#include "bubble.h"

static unsigned array[] = {
        1337, 1488, 228, 42, 2048, 0
};

static const size_t array_length =
        sizeof(array) / sizeof(array[0]);


int main() {
    for (size_t i = 0; i < array_length; i++) {
        printf("%u ", array[i]);
    }
    printf("\n");
    bubble_sort(array, array_length);

    for (size_t i = 0; i < array_length; i++) {
        printf("%u ", array[i]);
    }
}
