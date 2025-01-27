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
void test_push_pops(LLInt *list);
void test_get(LLInt *list);
void test_insert_remove(LLInt *list);
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
    // Fill list such that its values ascend from "left to right"
    // Size of the list should be RAND_MAX + 1;
    for (int i = MAX_SIZE; i >= 0; --i)
        assert(LLInt_push(list, LLIntNode_init(i)) == OK);
    fprintf(stderr, "List Len: %lu\n", LLInt_len(list));
    assert(LLInt_len(list) == MAX_SIZE + 1);
    
    // TODO: Create an LLInt_begin() accessor?
    LLIntNode *sigil = list->head->next;
    int test = 0;
    while (sigil->next)
    {
        fprintf(stderr, "Test: %d\tVal: %d\n", test, sigil->data);
        //assert(test == sigil->data);
        sigil = sigil->next;
        ++test;
    }
    fprintf(stderr, "Exit.\n");

    LLInt_destroy(list);
    return;
}

