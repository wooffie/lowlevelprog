#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "libHeap.h"

static heap *scanInput(char *input_file, bool type) {
    heap *h = maxHeap(0);
    h->max = type;
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
    return h;
}

static void printOutput(char *output_file, heap *h) {
    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }
    for (size_t i = 0; i < h->size; i++) {
        fprintf(fout, "%d %u\n", h->array[i].key, h->array[i].value);
    }
    fclose(fout);
}


static void sort(char *input_file, char *output_file) {
    heap *h = scanInput(input_file, false);
    heapSort(h->array, h->size);
    printOutput(output_file, h);
    heapRemove(h);
}

static void tree(char *input_file, char *output_file, bool type) {
    heap *h = scanInput(input_file, type);
    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }
    printHeap(h, fout);
    fclose(fout);
    heapRemove(h);

}

static void extract(char *input_file, char *output_file, bool type) {
    heap *h = scanInput(input_file, type);
    pair_heap root = heapRoot(h);
    printf("key=%d value=%u was extracted\n", root.key, root.value);
    printOutput(output_file, h);
    heapRemove(h);
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
                       "Sorting heap of integers - integers\n"
                       "Heap sort [-i] [input file] [-o] [output file] \n"
                       "Sorting array of integers\n"
                       "If you use input from CMD print any letter in the end\n"
                       "Heap (-max|-min) tree [-i] [input file] [-o] [output file]\n"
                       "Print heap\n"
                       "Heap (-max|-min) extract [-i] [input file] [-o] [output file]\n"
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
    } else if (strcmp(argv[2], "extract") == 0) {
        extract(input_file, output_file, type);
    }


    return 0;

}
