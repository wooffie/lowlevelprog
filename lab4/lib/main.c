#include <stddef.h>
#include <stdio.h>
#include "bubble.h"


int main() {

    static unsigned array[] = {
            1337, 1488, 228, 42, 2048, 0
    };

    static const size_t array_length =
            sizeof(array) / sizeof(array[0]);

    for (size_t i = 0; i < array_length; i++) {
        printf("%u ", array[i]);
    }
    printf("\n");
    bubble_sort(array, array_length);

    for (size_t i = 0; i < array_length; i++) {
        printf("%u ", array[i]);
    }
    printf("\n");

    static unsigned second_array[] = {
            10,9,8,7,6,5,4,3,2,1,0
    };

    static const size_t second_length =
            sizeof(second_array) / sizeof(second_array[0]);

    for (size_t i = 0; i < second_length; i++) {
        printf("%u ", second_array[i]);
    }
    printf("\n");
    bubble_sort(second_array, second_length);

    for (size_t i = 0; i < second_length; i++) {
        printf("%u ", second_array[i]);
    }


}
