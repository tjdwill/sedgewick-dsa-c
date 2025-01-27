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
void test_pushback_popback();
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
    test_pushback_popback();

    LLInt *list = LLInt_init();
    // Fill list such that its values ascend from "left to right"
    // Size of the list should be MAX_SIZE + 1;
    for (int i = MAX_SIZE; i >= 0; --i)
        assert(LLInt_push(list, LLIntNode_init(i)) == OK);
    assert(LLInt_len(list) == MAX_SIZE + 1);

    // TODO: Create an LLInt_begin() accessor?
    LLIntNode *sigil = list->head->next;
    int test = 0;
    while (sigil->next)
    {
        //fprintf(stderr, "Test: %d\tVal: %d\n", test, sigil->data);
        assert(test == sigil->data);
        sigil = sigil->next;
        ++test;
    }
    test_insert_remove(list);

    LLInt_destroy(list);
    return;
}

void test_pushback_popback()
{
    LLInt *list = LLInt_init();
    for (int i = 0; i < MAX_SIZE + 1; ++i)
        assert(LLInt_pushback(list, LLIntNode_init(i)) == OK);

    for (size_t i = LLInt_len(list); i > 0; --i)
    {
        LLIntNode *test;
        LLInt_popback(list, &test);
        assert(test->data == (int) i-1);
        LLIntNode_destroy(test);
    }
    LLInt_destroy(list);
    return;
}

void test_insert_remove(LLInt *list)
{
    size_t sz = LLInt_len(list);
    LLIntNode *item;

    // INVALID CASES
    assert(LLInt_remove(list, &item, sz+10) == BOUNDS_ERR);
    LLIntNode *test = LLIntNode_init(-1);
    assert(LLInt_insert(list,test, sz + 100) == BOUNDS_ERR);
    LLIntNode_destroy(test);

    // VALID CASES
    for (int i = 0; i < INNER_TEST_ITERS; ++i)
    {
        int idx = ranged_rand(0, MAX_SIZE);
        assert(LLInt_remove(list, &item, idx) == OK);
        // fprintf(stderr, "(test, val): (%d, %d)\n", idx, item->data);
        assert(item->data == idx);
        assert(LLInt_insert(list, item, idx) == OK);
    }

    //fprintf(stderr, "(start_sz, end_sz): (%lu, %lu)\n", sz, LLInt_len(list));
    assert(LLInt_len(list) == sz);
    return;
}
