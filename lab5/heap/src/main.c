#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "libHeap.h"

static void sort(char *input_file, char *output_file) {
    key_heap tmp = 0;
    key_heap *array = (key_heap *) malloc(sizeof(key_heap));
    size_t size = 0;
    unsigned int data = 1;
    FILE *fin = fopen(input_file, "r");
    if (strcmp(input_file, "") == 0) {

        fin = stdin;
    }
    int x;
    x = fscanf(fin, "%d", &tmp);
    while (x == 1) {
        if (size + 1 > data) {
            data *= 2;
            array = (key_heap *) realloc(array, sizeof(key_heap) * data);
        }
        array[size] = tmp;
        size++;
        x = fscanf(fin, "%d", &tmp);
    }
    fclose(fin);
    heapSort(array, size);

    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }
    for (size_t i = 0; i < size; i++) {
        fprintf(fout, "%d ", array[i]);
    }

    fclose(fout);
    free(array);

}

static void tree(char *input_file, char *output_file, bool type) {
    heap *h;
    if (type) {
        h = maxHeap(8);
    } else {
        h = minHeap(8);
    }

    FILE *fin = fopen(input_file, "r");
    if (strcmp(input_file, "") == 0) {
        printf("Print 1 node on 1 string like: key value\n");
        fin = stdin;
    }
    int x = 0;
    key_heap tmp_key = 0;
    value_heap tmp_value = 0;
    x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    while (x == 2) {
        heapAdd(h, (pair_heap) {tmp_key, tmp_value});
        x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    }
    fclose(fin);
    printHeap(h);
    heapRemove(h);

    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }


    fclose(fout);

}

static void insert(char *input_file, char *output_file, bool type) {
    heap *h;
    if (type) {
        h = maxHeap(8);
    } else {
        h = minHeap(8);
    }

    FILE *fin = fopen(input_file, "r");
    if (strcmp(input_file, "") == 0) {
        printf("Print 1 node on 1 string like: key value\n");
        fin = stdin;
    }
    int x = 0;
    key_heap tmp_key = 0;
    value_heap tmp_value = 0;
    x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    while (x == 2) {
        heapAdd(h, (pair_heap) {tmp_key, tmp_value});
        x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    }
    fclose(fin);
    pair_heap root = heapRoot(h);
    printf("key=%d value=%u was inserted\n", root.key, root.value);


    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }
    for (size_t i = 0; i < h->size; i++) {
        fprintf(fout, "%d %u\n", h->array[i].key, h->array[i].value);
    }
    heapRemove(h);
    fclose(fout);
}


int main(int argc, char *argv[]) {

    char *output_file = "";
    char *input_file = "";
    int output_arg = -1;
    int input_arg = -1;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (output_arg != -1) {
                printf("ILLEGAL FORMAT\n");
                return -1;
            } else {
                output_arg = i + 1;
            }
        }
        if (i == output_arg) {
            output_file = argv[i];
        }

        if (strcmp(argv[i], "-i") == 0) {
            if (input_arg != -1) {
                printf("ILLEGAL FORMAT\n");
                return -1;
            } else {
                input_arg = i + 1;
            }
        }
        if (i == input_arg) {
            input_file = argv[i];
        }
    }


    switch (argc) {
        case 1: {
            printf("Too few arguments, type --help for a list of options\n");
            return 0;
        }
        case 2: {
            if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
                printf(""
                       "Heap sort [-i] [input file] [-o] [output file] \n"
                       "Sorting array of integers\n"
                       "If you use input from CMD print any letter in the end\n"
                       "Heap (-max|-min) tree [-i] [input file] [-o] [output file]\n"
                       "Print heap\n"
                       "Heap (-max|-min) insert [-i] [input file] [-o] [output file]\n"
                       "Deleting max or min key in heap\n"
                );
                break;
            }

        }
        default: {
            break;
        }
    }

    bool type;
    if (strcmp(argv[1], "sort") == 0) {
        sort(input_file, output_file);
    } else if (strcmp(argv[1], "-max") == 0) {
        type = true;
    } else if (strcmp(argv[1], "-min") == 0) {
        type = false;
    } else {
        printf("Invalid input, check --help option");
    }

    if (strcmp(argv[2], "tree") == 0) {
        tree(input_file, output_file, type);
    } else if (strcmp(argv[2], "insert") == 0) {
        insert(input_file, output_file, type);
    }


    return 0;

}
