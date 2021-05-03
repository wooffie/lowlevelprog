#include "heap.h"
#include "CuTest.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// so trivial for easy checking =)
static bool heapIsValid(heap *h) {
    for (size_t i = 0; i < h->size; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        if (left < h->size) {
            if (h->max) {
                if (h->array[i].key < h->array[left].key) {
                    return false;
                }
            } else {
                if (h->array[i].key > h->array[left].key) {
                    return false;
                }
            }
        }
        if (right < h->size) {
            if (h->max) {
                if (h->array[i].key < h->array[right].key) {
                    return false;
                }
            } else {
                if (h->array[i].key > h->array[right].key) {
                    return false;
                }
            }
        }
    }
    return true;
}


static void TestHeapInit(CuTest *tc) {
    printf("1) Heap init test\n");
    heap *h = heapInit(0);
    CuAssertIntEquals_Msg(tc, "Heap with data 0 is created!", 1, h->data);

    h = heapInit(10);
    CuAssertIntEquals_Msg(tc, "Wrong amount of memory allocated!", sizeof(pair_heap) * 10, sizeof(pair_heap) * h->data);
    heapRemove(h);
}


static void TestShiftUp(CuTest *tc) {
    printf("2) Heap shift up test\n");
    heap *h = maxHeap(8);
    h->size = 4;
    pair_heap p[4] = {{8, 0},
                      {7, 0},
                      {4, 0},
                      {6, 0}}; // prepared heap
    for (size_t i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        h->array[i] = p[i];
    }
    heapAdd(h, (pair_heap) {10, 0});
    CuAssert(tc, "Prepared heap is wrong", heapIsValid(h));

    h->array[4] = (pair_heap) {10, 0};
    CuAssert(tc, "Changing element didn't brake heap", !heapIsValid(h));

    heapShiftUp(h, 4);
    CuAssert(tc, "Heap is wrong after shifting up", heapIsValid(h));
    heapRemove(h);

    heap *x = minHeap(1000);
    x->size = 1000;
    for (size_t i = 0; i < 999; i++) {
        x->array[i] = (pair_heap) {1, 0};
    }
    x->array[999] = (pair_heap) {0, 0};
    CuAssert(tc, "Prepared heap is valid!", !heapIsValid(x));

    heapShiftUp(x, 999);
    CuAssert(tc, "Heap is not valid!", heapIsValid(x));
    heapRemove(x);

}

static void TestShiftDown(CuTest *tc) {
    printf("3) Heap shift down test\n");
    heap *h = minHeap(8);
    h->size = 4;
    pair_heap p[4] = {{8, 0},
                      {7, 0},
                      {4, 0},
                      {7, 0}}; // prepared heap
    for (size_t i = 0; i < sizeof(p) / sizeof(p[0]); i++) {
        h->array[i] = p[i];
    }

    heapShiftDown(h, 0); // move 8 to the grandson
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));
    CuAssertIntEquals_Msg(tc, "Node with key 8 not shifted down", 4, h->array[0].key);

    heapShiftDown(h, 0); // move 8 to the grandson
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));
    CuAssertIntEquals_Msg(tc, "Node 4 shifted down", 4, h->array[0].key);
    heapRemove(h);

    heap *x = minHeap(1025);
    x->size = 1025;
    for (size_t i = 0; i < 1025; i++) {
        x->array[i] = (pair_heap) {128, 0};
    }
    x->array[0] = (pair_heap) {1024, 0};
    CuAssert(tc, "Prepared heap is valid!", !heapIsValid(x));

    heapShiftDown(x, 0);
    CuAssert(tc, "Heap is not valid!", heapIsValid(x));

    heapRemove(x);

}

static void TestHeapAdd(CuTest *tc) {
    printf("4) Heap add test\n");
    heap *h = minHeap(2);
    heapAdd(h, (pair_heap) {10, 0});
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));
    CuAssertIntEquals_Msg(tc, "Size of allocated memory increase, but shouldn't", 2, h->data);
    CuAssertIntEquals_Msg(tc, "Size of heap incorrect", 1, h->size);

    heapAdd(h, (pair_heap) {15, 0});
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));
    CuAssertIntEquals_Msg(tc, "Size of allocated memory dont increase, but should", 4, h->data);
    CuAssertIntEquals_Msg(tc, "Size of heap incorrect", 2, h->size);

    heapAdd(h, (pair_heap) {6, 0});
    CuAssert(tc, "Heap is not valid!", heapIsValid(h));
    heapRemove(h);
}

static int cmp(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

static void TestHeapRoot(CuTest *tc) {
    printf("5) Heap insert root test\n");
    heap *h = minHeap(16);
    key_heap array[10] = {23, 23, 42, 24, 22, 2, 42, 2222, 6464, 1};
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        heapAdd(h, (pair_heap) {array[i], 0});
    }

    qsort(array, sizeof(array) / sizeof(array[0]), sizeof(array[0]), cmp);
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        CuAssertIntEquals_Msg(tc, "Invalid item removed", array[i], heapRoot(h).key);
        CuAssert(tc, "Heap is not valid after extraction", heapIsValid(h));
    }
    heapRemove(h);

}

static void TestHeapArrays(CuTest *tc) {
    printf("6) Heap from arrays test\n");
    pair_heap p[10] = {{23,   0},
                       {23,   0},
                       {42,   0},
                       {24,   0},
                       {22,   0},
                       {2,    0},
                       {42,   0},
                       {2222, 0},
                       {6464, 0},
                       {1,    0}};

    heap *maxH = maxHeapArray(p, sizeof(p) / sizeof(p[0]));
    CuAssert(tc, "Max Heap is not valid!", heapIsValid(maxH));
    CuAssertIntEquals_Msg(tc, "Invalid size of heap", sizeof(p) / sizeof(p[0]), maxH->size);
    heapRemove(maxH);
    heap *minH = minHeapArray(p, sizeof(p) / sizeof(p[0]));
    CuAssert(tc, "Min Heap is not valid!", heapIsValid(minH));
    CuAssertIntEquals_Msg(tc, "Invalid size of heap", sizeof(p) / sizeof(p[0]), minH->size);
    heapRemove(minH);
}


static void HeapSortTest(struct CuTest *tc) {
    printf("7) HeapSort test\n");
    for (size_t i = 0; i < 100; i++) {
        size_t array_size = rand() % 1000 + 1;
        key_heap *array_ex = (key_heap *) malloc(sizeof(key_heap) * array_size);
        key_heap *array_ac = (key_heap *) malloc(sizeof(key_heap) * array_size);
        for (size_t j = 0; j < array_size; j++) {
            key_heap next = rand();
            array_ex[j] = next;
            array_ac[j] = next;
        }

        qsort(array_ex, array_size, sizeof(key_heap), cmp);
        heapSort(array_ac, array_size);

        for (size_t j = 0; j < array_size; j++) {
            CuAssertIntEquals_Msg(tc, "HeapSort is invalid", array_ex[j], array_ac[j]);
        }

    }

}


static CuSuite *StrUtilGetSuite() {
    printf("Tests:\n");
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestHeapInit);
    SUITE_ADD_TEST(suite, TestShiftUp);
    SUITE_ADD_TEST(suite, TestShiftDown);
    SUITE_ADD_TEST(suite, TestHeapAdd);
    SUITE_ADD_TEST(suite, TestHeapRoot);
    SUITE_ADD_TEST(suite, TestHeapArrays);
    SUITE_ADD_TEST(suite, HeapSortTest);
    return suite;
}


static void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, StrUtilGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    printf("Printing MAX heap example:\n");
    size_t array_size = 15;
    pair_heap *array = (pair_heap *) malloc(sizeof(pair_heap) * array_size);
    for (size_t j = 0; j < array_size; j++) {
        array[j] = (pair_heap) {rand() % 1000, rand() % 42};
    }
    heap *h = maxHeapArray(array, array_size);
    printHeap(h);
    heapRemove(h);
    free(array);
}


int main(void) {
    RunAllTests();
}

