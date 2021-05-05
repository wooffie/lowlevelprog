#include "heap.h"
#include "libHeap.h"

/*
 * Checking equality of keys
 * This function need for easy coding with both types of heaps
 */
bool compare(const heap *h, const size_t i, const size_t j) {
    const int result = (int) h->array[i].key - (int) h->array[j].key;
    if (result > 0) {
        return true;
    } else {
        return false;
    }
}

/*
 * Initialization of heap
 * Allocating memory for array, and also for heap (to free it after)
 * Using start data as param (can be useful for some functions)
 *
 * It not included in lib api, because user should use maxHeap or minHeap
 */
heap *heapInit(const unsigned int start_data) {
    heap *h = (heap *) malloc(sizeof(heap));
    h->array = (pair_heap *) malloc(sizeof(pair_heap) * start_data);
    h->data = start_data ? start_data : 1;
    h->size = 0;
    return h;
}

/*
 * Initialization of max heap
 * Uses heapInit and choose type in bool
 */
heap *maxHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);
    h->max = true;
    return h;
}

/*
 * Initialization of min heap
 * Uses heapInit and choose type in bool
 */
heap *minHeap(const unsigned int start_data) {
    heap *h = heapInit(start_data);
    h->max = false;
    return h;
}

/*
 * Need to restore characteristic of heap
 * If element not in place, we should move it UP in heap, until it takes its place
 * i - depth of using
 * time complexity in worst case - O(log(i))
 */
void heapShiftUp(heap *h, size_t i) {
    while ((compare(h, i, (i - 1) / 2) == h->max) && (i >= 1)) {
        const pair_heap tmp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = tmp;
        i = (i - 1) / 2;
    }
}

/*
 * Need to restore characteristic of heap
 * If element not in place, we should move it DOWN in heap, until it takes its place
 * i - depth of using
 * time complexity in worst case - O(log(i))
 */
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

/*
 * Add element to heap and restore characteristic
 * time complexity in worst case - O(log(N)), where N - size of heap
 */
void heapAdd(heap *h, pair_heap p) {
    if (h->size + 1 >= h->data) {
        h->data *= 2;
        h->array = (pair_heap *) realloc(h->array, h->data * sizeof(pair_heap));
    }
    h->array[(h->size)++] = p;
    heapShiftUp(h, h->size - 1);
}

/* Extract min/max element from heap
 * time complexity in worst case - O(log(N)), where N - size of heap
 */
pair_heap heapRoot(heap *h) {
    const pair_heap min = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapShiftDown(h, 0);
    return min;
}

/*
 * Restore heap with *random* array
 * time complexity maybe O(N), N - size of array
 */
static void buildHeap(heap *h) {
    for (size_t i = h->size / 2; i <= h->size / 2; i--) {
        heapShiftDown(h, i);
    }
}

/*
 * Creating minHeap from array
 * time complexity maybe O(N), N - size of array
 */
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

/*
 * Creating maxHeap from array
 * time complexity maybe O(N), N - size of array
 */
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

/*
 * Heap sort of array with help of Heap
 * time complexity should be O(N*log(N)), N - size of array
 */
void heapSort(pair_heap *array, size_t size) {
    heap *h = maxHeapArray(array, size); // O(N)
    while (h->size != 0) { // O(N)
        array[h->size - 1] = heapRoot(h); // O(logN)
    }
    free(h);
}

/*
 * Free allocated memory for Heap and Heap array
 */
void heapRemove(heap *h) {
    free(h->array);
    free(h);
}

/*
 * For printing
 */
static void printBT(heap *h, FILE *file, char *prefix, size_t index, bool isLeft) {
    if (index < h->size) {
        fprintf(file, "%s", prefix);
        fprintf(file, "%s", isLeft ? "|_" : "\\_");
        fprintf(file, "%d (%u)_\n", h->array[index].key, h->array[index].value);

        char buff[256];
        snprintf(buff, sizeof(buff), "%s%s", prefix, isLeft ? "|   " : "    ");
        printBT(h, file, buff, index * 2 + 1, true);
        printBT(h, file, buff, index * 2 + 2, false);
    } else {
        fprintf(file, "%s\n", prefix);
    }
}

/*
 * Printing heap like tree, output in file or cmd
 */
void printHeap(heap *h, FILE *file) {
    printBT(h, file, "", 0, false);
}
