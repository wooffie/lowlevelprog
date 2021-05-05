
#ifndef HEAP_LIBHEAP_H
#define HEAP_LIBHEAP_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef int key_heap;
typedef unsigned int value_heap;

typedef struct {
    key_heap key;
    value_heap value;
} pair_heap;

typedef struct {
    pair_heap *array;
    size_t size;
    unsigned int data;
    bool max;
} heap;

extern heap *maxHeap(unsigned int start_data);

extern heap *minHeap(unsigned int start_data);

extern void heapAdd(heap *h, pair_heap p);

extern pair_heap heapRoot(heap *h);

extern void heapRemove(heap *h);

extern void heapSort(pair_heap *array, size_t size);

extern heap *minHeapArray(pair_heap *p, size_t size);

extern heap *maxHeapArray(pair_heap *p, size_t size);

extern void printHeap(heap *h, FILE* file);

#endif
