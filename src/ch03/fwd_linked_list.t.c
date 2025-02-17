// fwd_linked_list.t.c
#include "linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>  // rand

#define MAX_SIZE 1000
#define INNER_TEST_ITERS 1000

// Inclusive random within established range
static int ranged_rand(int min, int max)
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
    fllint *list = init_fllint();
    // Fill list such that its values ascend from "left to right"
    // Size of the list should be RAND_MAX + 1;
    for (int i = MAX_SIZE; i >= 0; --i)
        fllint_push(list, init_fllint_node(i));
    assert(fllint_len(list) == MAX_SIZE + 1);

    test_get(list);
    //test_push_pops(list);
    //test_insert_remove(list);
    
    fllint_delete(list);
}

void test_get(fllint *list)
{
    fllint_node *item;
    int idx;
    //fprintf(stdout, "<test_get>\n----------\n");
    for (int i = 0; i < INNER_TEST_ITERS; ++i)
    {
        idx = ranged_rand(0, MAX_SIZE);
        //fprintf(stdout, "Idx: %d\n", idx);
        assert(fllint_get(list, idx, &item) == OK);
        //fprintf(stdout, "GOT: %d\n", item->data);
        assert(item->data == idx);
    }
    return;
}

void test_push_pops(fllint *list)
{
    assert(!fllint_empty(list));
    size_t sz = fllint_len(list);
    fllint_node *item;
    assert(fllint_get(list, sz + 5, &item) == BOUNDS_ERR);
    assert(fllint_get(list, 0, &item) == OK);
    int val = item->data;
    
    assert(fllint_pop(list, &item) == OK);
    assert(fllint_len(list) == sz-1);
    assert(fllint_push(list, item) == OK);
    assert(fllint_len(list) == sz);

    assert(fllint_get(list, 0, &item) == OK);
    assert(item->data == val);

    return;
}

void test_insert_remove(fllint *list)
{
    size_t sz = fllint_len(list);
    fllint_node *item;

    // INVALID CASES
    assert(fllint_remove(list, sz+10, &item) == BOUNDS_ERR);
    fllint_node *test = init_fllint_node(-1);
    assert(fllint_insert(list, test, sz + 100) == BOUNDS_ERR);
    free(test);

    // VALID CASES
    for (int i = 0; i < INNER_TEST_ITERS; ++i)
    {
        int idx = ranged_rand(0, MAX_SIZE);
        assert(fllint_remove(list, idx, &item) == OK);
        assert(item->data == idx);
        assert(fllint_insert(list, item, idx) == OK);
    }

    assert(fllint_len(list) == sz);
    return;
}
