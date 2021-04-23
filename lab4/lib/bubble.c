#include <stdio.h>
#include <stddef.h>
#include "bubble.h"

void bubble_sort(unsigned *array, size_t size) {

    static unsigned f = 0;

    for (size_t i = 0; i < size - 1; i++) {
        if (f == 1) {
            return;
        }
        f = 1; // If array sotred - quit
        for (size_t j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                const unsigned temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                f = 0;
            }
        }
    }
}