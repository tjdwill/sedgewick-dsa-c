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
        fllint_node *head = init_fllint_node(0);
        if (head)
            list->head = head;
        else 
        {
            free(head);
            free(list);
            return nullptr;
        }
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
    while(curr)
    {
        fllint_node *prev = curr;
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


//-------------------------------LLInt Implementation------------------------------------------

LLIntNode* LLIntNode_init(int k)
{
    LLIntNode* node = malloc(sizeof(LLIntNode));
    if (node)
    {
        node->data = k;
        node->next = nullptr;
        node->prev = nullptr;
    }
    return node;
}

void LLIntNode_destroy(LLIntNode *node)
{
    free(node);
    return;
}

LLInt* LLInt_init()
{
    LLInt* list = malloc(sizeof(LLInt));
    if (list)
    {
        LLIntNode* head = LLIntNode_init(-1);
        LLIntNode* tail = LLIntNode_init(-2);
        if (head && tail)
        {
            head->next = tail;
            tail->prev = head;

            list->head = head;
            list->tail = tail;
            list->sz = 0;
        }
        else
        {
            // Call destructors for the nodes
            // Due to `free` being no-op on nullptrs, we can safely call the destructors
            // even if the allocation failed on one.
            LLIntNode_destroy(head);
            LLIntNode_destroy(tail);
            free(list);
            return nullptr;
        }
    }
    return list;
}

void LLInt_destroy(LLInt *list)
{
    LLIntNode *curr = list->head;
    while(curr)
    {
        LLIntNode *prev = curr;
        curr = curr->next;
        LLIntNode_destroy(prev);
    }
    free(list);
    return;
}
//
//// MODIFIERS
//
LLStatus LLInt_insert(LLInt *list, LLIntNode *item, size_t pos)
{
    if (LLInt_empty(list))
    {
        // just insert the node.
        item->next = list->tail;
        item->prev = list->head;
        list->head->next = item;
        list->tail->prev = item;
        ++(list->sz);
        return OK;
    }
    if (pos > LLInt_len(list))
        return BOUNDS_ERR;
    // Traverse through the list and land ON the spot of insertion.
    // Place item before the present node.
    LLIntNode *curr;
    LLInt_walk_to(list, &curr, pos);
    // Now, curr is ON the place we want item to be, so move `curr` further toward the tail.
    LLIntNode *curr_prev = curr->prev;
    LLIntNode *curr_next = curr->next;
    curr_prev->next = item;
    curr_next->prev = item;

    item->prev = curr->prev;
    item->next = curr;
    curr->prev = item;
    // curr->next = curr->next // for completeness
    // Update size
    ++(list->sz);
    return OK;
}

LLStatus LLInt_push(LLInt *list, LLIntNode *item)
{
    return LLInt_insert(list, item, 0);
}

LLStatus LLInt_pushback(LLInt *list, LLIntNode *item)
{
    return LLInt_insert(list, item, LLInt_len(list));
}
//
//LLStatus LLInt_remove(LLInt *list, LLIntNode **ret, size_t pos)
//{}
//
//LLStatus LLInt_pop(LLInt *list, LLIntNode **ret)
//{}
//
//LLStatus LLInt_popback(LLInt *list, LLIntNode **ret)
//{}
//
//LLStatus LLInt_get(LLInt *list, LLIntNode **ret, size_t pos)
//{}

size_t LLInt_len(LLInt *list)
{
    return list->sz;
}

bool LLInt_empty(LLInt *list)
{
    return LLInt_len(list) == 0;
}

void LLInt_walk_to(LLInt *list, LLIntNode** pp_node, size_t pos)
{
    assert(!LLInt_empty(list));
    size_t sz = LLInt_len(list);
    assert(pos <= sz);  // LEQ in order to insert at the end of the list.
    // Choose which direction to begin from. Because LLInts are doubly-linked, we can walk
    // from either direction, meaning the worst-case time complexity is halved.
    if (sz - pos <= pos)
    {
        // Walk from the tail
        *pp_node = list->tail;
        for (size_t i = sz; i > pos; --i)
            *pp_node = (*pp_node)->prev;
    }
    else
    {
        // Walk from HEAD
        *pp_node = list->head;
        for (size_t i = 0; i < pos + 1; ++i) // Calculates how many times to move from HEAD
            *pp_node = (*pp_node)->next;
    }
    return;
}

