// linked_list.c
#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>  // malloc/free, size_t

fllint_node* init_fllint_node(int n)
{
   fllint_node* ptr = (fllint_node*) malloc(sizeof(fllint_node));
   if (ptr)
   {
       ptr->data = n;
       ptr->next = NULL;
   }
   return ptr;
}

fllint* init_fllint()
{
    fllint *list = (fllint*) malloc(sizeof(fllint));
    if (list)
    {
        list->sz = 0;
        // Create a dummy head to make implementations easier.
        list->head = init_fllint_node(0);
        assert(list->head);
    }
    return list;
}

LLStatus fllint_insert(fllint_node *node, size_t pos, fllint *list)
{
    if(pos > fllint_len(list))
        return BOUNDS_ERR;
    fllint_node *curr = list->head;
    for (size_t i = 0; i < pos; ++i)
        curr = curr->next;
    node->next = curr->next;
    curr->next = node;
    ++(list->sz);
    return OK;
}

LLStatus fllint_push(fllint_node *node, fllint *list)
{
    return fllint_insert(node, 0, list);
}

LLStatus fllint_remove(size_t pos, fllint_node **ret, fllint *list)
{
    if (fllint_len(list) < pos + 1)  // account for the dummy head
        return BOUNDS_ERR;
    fllint_node *curr = list->head;
    // Iterate until we find the node BEFORE the one to be removed.
    for (int i = 0; i < pos; ++i)
        curr = curr->next;
    fllint_node* rm_node = curr->next;
    curr->next = rm_node->next;
    rm_node->next = NULL;
    // Update return value and list size
    *ret = rm_node;
    --(list->sz);
    return OK;
}

LLStatus fllint_pop(fllint_node **ret, fllint *list)
{
    return fllint_remove(0, ret, list);
}

void fllint_delete(fllint *list)
{
    fllint_node *curr = list->head;
    fllint_node *prev;
    while(curr)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
    return;
}
// ACCESSORS

LLStatus fllint_get(size_t pos, fllint_node **item, fllint *list)
{
    if (fllint_len(list) < pos + 1)
        return BOUNDS_ERR;
    fllint_node *curr = list->head;
    // Iterate until we find the node BEFORE the one to be removed.
    for (size_t i = 0; i < pos; ++i)
        curr = curr->next;
    *item = curr->next;
    return OK;
}

size_t fllint_len(fllint *list)
{
    return list->sz;
}
bool fllint_empty(fllint *list)
{
    return fllint_len(list) == 0;
}
