// btree.h
// Implementing a simple binary tree in C
//
#ifndef INCLUDED_DSA_BTREE
#define INCLUDED_DSA_BTREE

#include <stddef.h>

struct dbtreenode
{
    void                *data;
    size_t              dsize;  // the size of the stored data
    struct dbtreenode   *left_child;
    struct dbtreenode   *right_child;
};
typedef struct dbtreenode BTreeNode;

/// Initialize a bare BTreeNode
/// Takes a data size parameter to keep track of 
/// the size the user uses for data.
BTreeNode* BTreeNode_construct(size_t dsize);

/// Deletes the given object, freeing the underlying memory.
/// Since this would have to be recursive in nature, implement traversal first.
/// This function assumes the left and right children are already nulled.
void BTreeNode_destroy(BTreeNode *node);
/// An implementation function for the destruction function.
/// This should never be used by the user.
void BTreeNode_destroyimpl(BTreeNode *node);
/// Traverse the tree using the postorder method and perform the provided
/// operation.
void BTreeNode_traverse_postorder(
        BTreeNode *root,
        // void (*TraverseOrder)(BTreeNode *node),
        void (*Operation)(BTreeNode *node)
);

#endif // INCLUDED_DSA_BTREE
