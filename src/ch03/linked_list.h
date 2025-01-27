// linked_list.h
// Basic Linked List implementation for practice
#ifndef INCLUDED_DSA_LINKED_LIST
#define INCLUDED_DSA_LINKED_LIST
/*
 * A linked list is a series of nodes wired together.
 * Each list has a HEAD and a TAIL.
 * The HEAD is the beginning of the list. It's semantic
 * function is to simply tell us *where* the list begins.
 * Similarly, the TAIL tells us where the list terminates.
 *
 * Features:
 *      - Insertion
 *      - Removal
 *      - Push
 *      - Pop
 */
#include <stdlib.h>  // size_t

/// Error enum for the linked list API
typedef enum 
{
    OK,
    BOUNDS_ERR,
    ALLOC_FAIL
} LLStatus;


/// Define the node for a singly-linked list (forward list). 
/// It is assumed that the data member will be a int.
typedef struct 
{
    int data;
    void *next;
} fllint_node;

/// Construct a node for a forward list of ints.
/// Returns `nullptr` if allocation fails.
fllint_node* init_fllint_node(int n);


/// A singly-linked list of ints.
/// This list can only be traversed in one direction.
typedef struct 
{
    size_t sz; // READ-ONLY
    fllint_node *head;
} fllint; 

/// Initialize an empty list
fllint* init_fllint();

// MANIPULATORS
// All manipulator functions assume a valid list.

/// Insert the value at the specified position of the input list.
/// Takes ownership of the node object.
LLStatus fllint_insert(fllint_node *node, size_t pos, fllint *list);
/// Insert element at front of the list.
/// - Assumes the list is valid.
/// - Takes ownership of the node object.
/// - O(1) insertion time.
LLStatus fllint_push(fllint_node *node, fllint *list);
/// Remove the node at the specified location.
/// YOU assume responsiblity for deleting the node object.
LLStatus fllint_remove(size_t pos, fllint_node **ret, fllint *list);
/// Remove front element.
/// Returns BOUNDS_ERR if list is empty before this function is called.
/// YOU assume responsiblity for deleting the node object.
LLStatus fllint_pop(fllint_node **ret, fllint *list);

/// Deletes the entire list, freeing the allocated memory.
void fllint_delete(fllint *list);

// ACCESSORS

/// Get the node at position pos.
LLStatus fllint_get(size_t pos, fllint_node **item, fllint *list);
/// Get the number of elements in the list.
/// Assumes a valid list.
size_t fllint_len(fllint *list);
bool fllint_empty(fllint *list);

//-----------------------------------------------------------------------------
/*
 * I'm still trying to figure out how to design C APIs, so for the following one,
 * I will place the relevant object as the first parameter for each function instead
 * of the last.
 */

/// LLIntNode
/// ---------
///
/// A type that contains the data for an entry in the linked list.
typedef struct
{
    int data;
    void *prev;
    void *next;
} LLIntNode;

/// Initialize a node, returning `nullptr` if the
/// allocation fails.
LLIntNode* LLIntNode_init(int k);
/// LLInt (Linked List of Ints)
/// ---------------------------
///
/// Doubly-linked list of ints. Keeps track of its size to assist with bounds checking.
typedef struct 
{
    size_t sz;
    LLIntNode *head;
    LLIntNode *tail;

} LLInt;

// CONSTRUCTION/DESTRUCTION

/// LLInt Constructor
LLInt* LLInt_init();
/// LLInt Destructor
void LLInt_delete(LLInt *list);

// MODIFIERS

/// Insert the element at the specified position, transferring ownership to the list.
LLStatus LLInt_insert(LLInt *list);
/// Insert the element at the front of the list, transferring ownership to the list.
LLStatus LLInt_push(LLInt *list, LLIntNode **ret);
/// Insert the element at the back of the list, transferring ownership to the list.
LLStatus LLInt_pushback(LLInt *list, LLIntNode **ret);
/// Remove the element at the specified position, transferring ownership to the caller.
LLStatus LLInt_remove(LLInt *list, LLIntNode **ret, size_t pos);
/// Remove the element at the front position, transferring ownership to the caller.
LLStatus LLInt_pop(LLInt *list, LLIntNode **ret);
/// Remove the element at the back position, transferring ownership to the caller.
LLStatus LLInt_popback(LLInt *list, LLIntNode **ret);

// ACCESSORS

/// Retrieve a (non-owning) reference to the element at the specified position.
LLStatus LLInt_get(LLInt *list, LLIntNode **ret, size_t pos);
/// Get the number of elements in the list.
/// Assumes a valid list.
size_t LLInt_len(LLInt *list);
bool LLInt_empty(LLInt *list);

// UTILS

/// A centralized traversal method. This way, I only need to change traversal in one place
/// if the implementation changes. Assumes `pos` is a valid access index and that the list
/// is valid.
void LLInt_walk_to(LLInt *list, LLIntNode** pp_node, size_t pos);
#endif // INCLUDED_DSA_LINKED_LIST
