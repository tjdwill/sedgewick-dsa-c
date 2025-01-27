// linked_list.t.c
#include "linked_list.h"
//- Standard Library
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>  // rand

#define MAX_SIZE 1000
#define INNER_TEST_ITERS 1000

// Inclusive random within established range
static inline int ranged_rand(int min, int max)
{
    // https://stackoverflow.com/a/1202706
    return rand() % (max + 1 - min) + min;
}
void test_push_pops(fllint *list);
void test_get(fllint *list);
void test_insert_remove(fllint *list);
void test_delete(fllint *list);
void run_tests();

int main(int argc, char* argv[])
{
    if (argc != 2)
        fprintf(stderr, "Usage: llTest <NUM_LOOPS>\n");
    int iterations = atoi(argv[1]);
    // Run at least once
    if (iterations <= 0)
        iterations = 1;
    for (int i = 0; i < iterations; ++i)
        run_tests();
}

void run_tests()
{
    LLInt *list = LLInt_init();

    LLInt_delete(list);
    return;
}
