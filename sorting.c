#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define OPTIONS "Hasbhqn:p:r:"

#define HEAP    1
#define BATCHER 2
#define SHELL   3
#define QUICK   4
#define MENU    5

int main(int argc, char **argv) {

    int opt = 0;

    //Create Sets object
    Set sets = set_empty();

    //Create statistics object
    Stats stats;

    //Default seed value for random number generation
    uint32_t seed = 13371453;

    //Default length value for array
    uint32_t length = 100;

    //Default array elements length to be printed
    uint32_t elements = 100;

    //Flag to keep track of whether or not the menu should be printed
    int menu_flag = 0;

    //If there is no input by the user, the flag is activated to print out the menu
    if (argc == 1) {
        menu_flag = 1;
    }

    //Loop through the user inputs
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        //Switch statement that change our set depending on which sort the user has specified
        switch (opt) {
        case 'a':
            sets = set_insert(sets, HEAP);
            sets = set_insert(sets, BATCHER);
            sets = set_insert(sets, SHELL);
            sets = set_insert(sets, QUICK);
            break;
        case 'h': sets = set_insert(sets, HEAP); break;
        case 'b': sets = set_insert(sets, BATCHER); break;
        case 's': sets = set_insert(sets, SHELL); break;
        case 'q': sets = set_insert(sets, QUICK); break;
        //Change the default seed if the user has provided one
        case 'r': seed = (uint32_t) strtoul(optarg, NULL, 10); break;
        //Change the default length if the user has provided one
        case 'n': length = (uint32_t) strtoul(optarg, NULL, 10); break;
        //Change the default elements to be printed if the user has provided one
        case 'p': elements = (uint32_t) strtoul(optarg, NULL, 10); break;
        //Add menu to set
        case 'H': sets = set_insert(sets, MENU); break;
        default: sets = set_insert(sets, MENU); break;
        }
    }

    //Edits set for menu (If user has any inputs along with -H, onlt the menu gets printed)
    if (set_member(sets, MENU)) {
        sets = set_empty();
        sets = set_insert(sets, MENU);
    }

    //Set the seed
    srandom(seed);

    //Create dynamically allocated array and set random values for its elements

    uint32_t *tArray = (uint32_t *) malloc(length * sizeof(uint32_t));

    for (int i = 0; i < length; i++) {
        tArray[i] = random() & ((1 << 30) - 1);
    }

    //For this series of print statements, a new dynamically allocated array is created
    //This array copies the values of the tArray and does the sort with that. After
    //all data is calculated and returned, the space is freed up and the array is set to NULL

    if (set_member(sets, SHELL)) {
        uint32_t *shell_array = (uint32_t *) malloc(length * sizeof(uint32_t));
        memcpy(shell_array, tArray, length * sizeof(uint32_t));
        shell_sort(&stats, shell_array, length);
        printf("Shell Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", length,
            stats.moves, stats.compares);
        reset(&stats);
        for (int i = 0; i < length && i < elements; i++) {
            printf("%13d", shell_array[i]);
            if ((((i + 1) % 5) == 0) || i + 1 >= elements || i + 1 >= length) {
                printf("\n");
            }
        }
        free(shell_array);
        shell_array = NULL;
    }

    if (set_member(sets, BATCHER)) {
        uint32_t *batcher_array = (uint32_t *) malloc(length * sizeof(uint32_t));
        memcpy(batcher_array, tArray, length * sizeof(uint32_t));
        batcher_sort(&stats, batcher_array, length);
        printf("Batcher Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", length,
            stats.moves, stats.compares);
        reset(&stats);
        for (int i = 0; i < length && i < elements; i++) {
            printf("%13d", batcher_array[i]);
            if ((((i + 1) % 5) == 0) || i + 1 >= elements || i + 1 >= length) {
                printf("\n");
            }
        }
        free(batcher_array);
        batcher_array = NULL;
    }

    if (set_member(sets, HEAP)) {
        uint32_t *heap_array = (uint32_t *) malloc(length * sizeof(uint32_t));
        memcpy(heap_array, tArray, length * sizeof(uint32_t));
        heap_sort(&stats, heap_array, length);
        printf("Heap Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", length,
            stats.moves, stats.compares);
        reset(&stats);
        for (int i = 0; i < length && i < elements; i++) {
            printf("%13d", heap_array[i]);
            if ((((i + 1) % 5) == 0) || i + 1 >= elements || i + 1 >= length) {
                printf("\n");
            }
        }
        free(heap_array);
        heap_array = NULL;
    }

    if (set_member(sets, QUICK)) {
        uint32_t *quick_array = (uint32_t *) malloc(length * sizeof(uint32_t));
        memcpy(quick_array, tArray, length * sizeof(uint32_t));
        quick_sort(&stats, quick_array, length);
        printf("Quick Sort, %d elements, %" PRIu64 " moves, %" PRIu64 " compares\n", length,
            stats.moves, stats.compares);
        reset(&stats);
        for (int i = 0; i < length && i < elements; i++) {
            printf("%13d", quick_array[i]);
            if ((((i + 1) % 5) == 0) || i + 1 >= elements || i + 1 >= length) {
                printf("\n");
            }
        }
        free(quick_array);
        quick_array = NULL;
    }
    //Conditional for the menu to be printed for the user
    if (set_member(sets, MENU) || menu_flag == 1) {
        if (menu_flag == 1) {
            printf("Select at least one sort to perform.\n");
        }
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\n");
        printf("USAGE\n   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n");
        printf("   -H              Display program help and usage.\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -b              Enable Batcher Sort.\n");
        printf("   -h              Enable Heap Sort.\n");
        printf("   -q              Enable Quick Sort.\n");
        printf("   -n length       Specify number of array elements (default: 100).\n");
        printf("   -p elements     Specify number of elements to print (default: 100).\n");
        printf("   -r seed         Specify random seed (default: 13371453).\n");
    }

    free(tArray);
    tArray = NULL;
}
