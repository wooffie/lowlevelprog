#include "heap.h"
#include "malloc.h"
#include <stdbool.h>
#include <stdio.h>


bool compare(const heap *h, const size_t i, const size_t j) {
    const int result = (int) h->array[i].key - (int) h->array[j].key;
    if (result > 0) {
        return true;
    } else {
        return false;
    }
}

heap *heapInit(const unsigned int start_data) {
    heap *h = (heap *) malloc(sizeof(heap));
    h->array = (pair_heap *) malloc(sizeof(pair_heap) * start_data);
    h->data = start_data ? start_data : 1;
    h->size = 0;
    return h;
}


heap *maxHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);
    h->max = true;
    return h;
}

heap *minHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);
    h->max = false;
    return h;
}


void heapShiftUp(heap *h, size_t i) {
    while ((compare(h, i, (i - 1) / 2) == h->max) && (i >= 1)) {
        const pair_heap tmp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
}

void heapShiftDown(heap *h, size_t i) {
    while (2 * i + 1 < h->size) {
        const size_t left = 2 * i + 1;
        const size_t right = 2 * i + 2;
        size_t j = left;

        if ((right < h->size) && (compare(h, right, left) == h->max)) {
            j = right;
        }
        if (compare(h, i, j) == h->max) {
            break;
        }
        const pair_heap tmp = h->array[i];
        h->array[i] = h->array[j];
        h->array[j] = tmp;
        i = j;
    }
}


void heapAdd(heap *h, pair_heap p) {
    if (h->size + 1 >= h->data) {
        h->data *= 2;
        h->array = (pair_heap *) realloc(h->array, h->data * sizeof(pair_heap));
    }
    h->array[(h->size)++] = p;
    heapShiftUp(h, h->size - 1);
}

pair_heap heapRoot(heap *h) {
    const pair_heap min = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapShiftDown(h, 0);
    return min;
}

void buildHeap(heap *h) {
    for (size_t i = h->size / 2; i <= h->size / 2; i--) {
        heapShiftDown(h, i);
    }
}

heap *minHeapArray(pair_heap *p, size_t size) {

    heap *h = heapInit(size);

    for (size_t i = 0; i < size; i++) {
        h->array[i] = p[i];
    }
    h->data = size;
    h->size = size;
    h->max = false;

    buildHeap(h);
    return h;
}

heap *maxHeapArray(pair_heap *p, size_t size) {

    heap *h = heapInit(size);

    for (size_t i = 0; i < size; i++) {
        h->array[i] = p[i];
    }
    h->data = size;
    h->size = size;
    h->max = true;

    buildHeap(h);
    return h;
}

void heapSort(key_heap *array, size_t size) {
    pair_heap *array_pairs = (pair_heap *) malloc(sizeof(pair_heap) * size);
    for (size_t i = 0; i < size; i++) {
        array_pairs[i] = (pair_heap) {array[i], 0};
    }
    heap *h = minHeapArray(array_pairs, size);
    for (size_t i = 0; i < size; i++) {
        array[i] = heapRoot(h).key;
    }

    free(array_pairs);
    heapRemove(h);
}


void heapRemove(heap *h) {
    free(h->array);
    free(h);
}

void printBT(heap *h, char *prefix, size_t index, bool isLeft) {
    if (index < h->size) {
        printf("%s", prefix);
        printf("%s", isLeft ? "|-" : "\\-");
        printf("%zu (%u)\n", h->array[index].key, h->array[index].value);

        char buff[256];
        snprintf(buff, sizeof(buff), "%s%s", prefix, isLeft ? "|   " : "    ");
        printBT(h, buff, index * 2 + 1, true);
        printBT(h, buff, index * 2 + 2, false);
    } else {
        printf("%s\n", prefix);
    }
}

void printHeap(heap *h) {
    printBT(h, "", 0, false);
}
