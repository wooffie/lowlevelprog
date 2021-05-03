
#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <stddef.h>
#include <stdbool.h>
#include "libHeap.h"



typedef size_t key_heap;
typedef unsigned int value_heap;

extern heap *heapInit(unsigned int start_data);

extern void heapShiftUp(heap *h, size_t i);

extern void heapShiftDown(heap *h, size_t i);


#endif
