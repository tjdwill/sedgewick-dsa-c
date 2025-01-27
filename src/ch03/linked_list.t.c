// linked_list.t.c
#include "linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>  // rand

#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX 1000
#define INNER_TEST_ITERS 1000


void test_push_pops(fllint *list);
void test_get(fllint *list);
void test_insert_remove(fllint *list);
void test_delete(fllint *list);
void run_tests();

int main(int argc, char* argv[])
{
    assert(RAND_MAX == 1000);
    if (argc != 2)
        fprintf(stderr, "Usage: llTest <NUM_LOOPS>");
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
    for (int i = RAND_MAX; i >= 0; --i)
        fllint_push(init_fllint_node(i), list);
    assert(fllint_len(list) == RAND_MAX + 1);

    test_get(list);
    test_push_pops(list);
    test_insert_remove(list);
    
    fllint_delete(list);
}

void test_get(fllint *list)
{
    fllint_node *item;
    int idx;
    for (int i = 0; i < INNER_TEST_ITERS; ++i)
    {
        idx = rand();
        assert(fllint_get(idx, &item, list) == OK);
        assert(item->data == idx);
    }
    return;
}

void test_push_pops(fllint *list)
{
    assert(!fllint_empty(list));
    size_t sz = fllint_len(list);
    fllint_node *item;
    assert(fllint_get(sz + 5, &item, list) == BOUNDS_ERR);
    assert(fllint_get(0, &item, list) == OK);
    int val = item->data;
    
    assert(fllint_pop(&item, list) == OK);
    assert(fllint_len(list) == sz-1);
    assert(fllint_push(item, list) == OK);
    assert(fllint_len(list) == sz);

    assert(fllint_get(0, &item, list) == OK);
    assert(item->data == val);

    return;
}

void test_insert_remove(fllint *list)
{
    size_t sz = fllint_len(list);
    fllint_node *item;

    // INVALID CASES
    assert(fllint_remove(sz+10, &item, list) == BOUNDS_ERR);
    fllint_node *test = init_fllint_node(-1);
    assert(fllint_insert(test, sz + 100, list) == BOUNDS_ERR);
    free(test);

    // VALID CASES
    for (int i = 0; i < INNER_TEST_ITERS; ++i)
    {
        int idx = rand();
        assert(fllint_remove(idx, &item, list) == OK);
        assert(item->data == idx);
        assert(fllint_insert(item, idx, list) == OK);
    }

    assert(fllint_len(list) == sz);
    return;
}
