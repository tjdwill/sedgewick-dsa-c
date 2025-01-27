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

LLInt* LLInt_init()
{
    LLInt* list = malloc(sizeof(LLInt));
    if (list)
    {
        LLIntNode* head = LLIntNode_init(-1);
        LLIntNode* tail = LLIntNode_init(-1);
        if (head && tail)
        {
            head->next = tail;
            tail->prev = head;

            list->head = head;
            list->tail = tail;
        }
        else
        {
            // free all pointers and return nullptr
            // free is nopt on nullptr, so it's safe to call
            free(head);
            free(tail);
            free(list);
            return nullptr;
        }
    }
    return list;
}

void LLInt_delete(LLInt *list)
{
    LLIntNode *curr = list->head;
    while(curr)
    {
        LLIntNode *prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
    return;
}
//
//// MODIFIERS
//
//LLStatus LLInt_insert(LLInt *list)
//{}
//
//LLStatus LLInt_push(LLInt *list, LLIntNode **ret)
//{}
//
//LLStatus LLInt_pushback(LLInt *list, LLIntNode **ret)
//{}
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
//// ACCESSORS
//
//LLStatus LLInt_get(LLInt *list, LLIntNode **ret, size_t pos)
//{}
//
//size_t LLInt_len(LLInt *list)
//{}
//
//bool LLInt_empty(LLInt *list)
//{}
//
//// UTILS
//
//
//
//
//void LLInt_walk_to(LLInt *list, LLIntNode** pp_node, size_t pos)
//{}

