#include <string.h>
#include "libHeap.h"

/*
 * Made a separate function for reading heaps from files or cmd
 * char *input_file - file with heap, if equals ("") - read from cmd
 * type - to determine type of tree
 */
static heap *scanInput(char *input_file, bool type) {
    heap *h = maxHeap(0);
    h->max = type;
    FILE *fin = fopen(input_file, "r");
    if (strcmp(input_file, "") == 0) {
        printf("Print one key int with one value int like:\n key value\n");
        fin = stdin;
    }
    int x = 0;
    key_heap tmp_key = 0;
    value_heap tmp_value = 0;
    // like scanf but with selection of stream
    x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    // equals 2 because we should find two variables per string
    while (x == 2) {
        heapAdd(h, (pair_heap) {tmp_key, tmp_value});
        x = fscanf(fin, "%d %u\n", &tmp_key, &tmp_value);
    }
    fclose(fin);
    return h;
}

/*
 * Made a separate function for write heaps
 * char *output_file - file to write, if equals ("") - write to cmd
 * *h - heap to print
 */
static void printOutput(char *output_file, heap *h) {
    FILE *fout = fopen(output_file, "w");
    if (strcmp(output_file, "") == 0) {
        fout = stdout;
    }
    for (size_t i = 0; i < h->size; i++) {
        // like printf but with selection of stream
        fprintf(fout, "%d %u\n", h->array[i].key, h->array[i].value);
    }
    fclose(fout);
}

/*
 * Sorting heap
 */
static void sort(char *input_file, char *output_file) {
    heap *h = scanInput(input_file, false);
    heapSort(h->array, h->size);
    printOutput(output_file, h);
    heapRemove(h);
}

/*
 * Printing nice tree for heap
 */
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

/*
 * Take the biggest/smallest element and remove from heap
 * Printing extracted element
 * You can use in without output file to find min/max element
 * Or use with output in same file for saving changing
 *
 */
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

    // parse input and output files
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            // to restrict multidefining if output files
            if (output_arg != -1) {
                printf("ILLEGAL FORMAT\n");
                return -1;
            } else {
                output_arg = i + 1;
            }
        }
        // saving name of file
        if (i == output_arg) {
            output_file = argv[i];
        }

        if (strcmp(argv[i], "-i") == 0) {
            // to restrict multidefining if input files
            if (input_arg != -1) {
                printf("ILLEGAL FORMAT\n");
                return -1;
            } else {
                input_arg = i + 1;
            }
        }
        // saving name of file
        if (i == input_arg) {
            input_file = argv[i];
        }
    }

    if (argc == 1) {
        printf("Too few arguments, type --help for a list of options\n");
        return 0;
    } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf(""
               "Heap sort [-i] [input file] [-o] [output file] \n"
               "Sorting heap of integers - integers\n\n"
               "Heap sort [-i] [input file] [-o] [output file] \n"
               "Sorting array of integers\n\n"
               "If you use input from CMD print any letter in the end\n"
               "Heap (-max|-min) tree [-i] [input file] [-o] [output file]\n"
               "Print heap\n\n"
               "Heap (-max|-min) extract [-i] [input file] [-o] [output file]\n"
               "Deleting max or min key in heap\n\n"
        );
        return 0;
    }

    // resolving type of heap or sort-command
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
