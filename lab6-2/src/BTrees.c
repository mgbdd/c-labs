#include "BTrees.h"

BNode *CreateBNode(BTree *tree, bool *memFlag)
{
    BNode *node = malloc(sizeof(BNode));
    if (node == NULL)
    {
        *memFlag = 1;
        return node;
    }
    node->keysNum = 0;
    node->leaf = 1;
    node->keys = malloc(sizeof(int) * (2 * tree->degree - 1));
    if (node->keys == NULL)
    {
        *memFlag = 1;
        return node;
    }
    node->children = NULL;
    return node;
}

static void CreateChildren(BNode *node, BTree *tree, bool *memFlag)
{
    node->leaf = 0;
    node->children = malloc(sizeof(BNode *) * 2 * tree->degree);
    if (node->children == NULL)
    {
        *memFlag = 1;
    }
}

static bool NodeIsFull(BNode *node, BTree *tree)
{
    if (node->keysNum == 2 * tree->degree - 1)
    {
        return 1;
    }
    return 0;
}

static int GetKeyIndex(BNode *node, int key) 
{
    int left = 0, right = node->keysNum - 1;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (key <= node->keys[middle])
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return right + 1;
}

static void MoveKeys(BNode *oldNode, int ind1, BNode *newNode, int ind2)
{
    int moveInd = newNode->keysNum - ind2;
    memmove(newNode->keys + ind2, oldNode->keys + ind1, moveInd * sizeof(int));
    if (oldNode->leaf == 0)
    {
        memmove(newNode->children + ind2, oldNode->children + ind1, (moveInd + 1) * sizeof(BNode *));
    }
}

static void Separate(int moveInd, BNode *parent, BTree *tree, bool *memFlag)
{
    BNode *oldChild = parent->children[moveInd]; 
    BNode *newChild = CreateBNode(tree, memFlag);
    if (oldChild->leaf == 0)
    {
        CreateChildren(newChild, tree, memFlag);
    } 
    newChild->keysNum = tree->degree - 1;
    MoveKeys(oldChild, tree->degree, newChild, 0); 
    oldChild->keysNum = tree->degree - 1;
    parent->keysNum++;
    MoveKeys(parent, moveInd, parent, moveInd + 1);
    parent->keys[moveInd] = oldChild->keys[tree->degree - 1];
    parent->children[moveInd + 1] = newChild;
}

static void InsertInNode(BNode *node, int key)
{
    int ind = GetKeyIndex(node, key);
    node->keysNum++;
    MoveKeys(node, ind, node, ind + 1);
    node->keys[ind] = key;
}

static void NotFullNodeCase(BTree *tree, BNode *node, int key, bool *memFlag)
{
    if (node->leaf == 1)
    {
        InsertInNode(node, key);
    } 
    else
    {
        int childInd = GetKeyIndex(node, key); 
        if (NodeIsFull(node->children[childInd], tree))
        {
            Separate(childInd, node, tree, memFlag);
        }
        NotFullNodeCase(tree, node->children[GetKeyIndex(node, key)], key, memFlag);
    }
}

void InsertInTree(BTree *tree, int key, bool *memFlag)
{
    if (NodeIsFull(tree->root, tree) == 1)
    {
        BNode *newRoot = CreateBNode(tree, memFlag);
        CreateChildren(newRoot, tree, memFlag);
        newRoot->children[0] = tree->root;
        Separate(0, newRoot, tree, memFlag);
        tree->root = newRoot;
        tree->height++;
    }
    NotFullNodeCase(tree, tree->root, key, memFlag);
}

void DeleteTree(BNode *root)
{
    free(root->keys);
    if (root->leaf == 1)
    {
        free(root);
        return;
    }
    else
        for (int i = 0; i <= root->keysNum; i++)
        {
            DeleteTree(root->children[i]);
        }
    free(root->children);
    free(root);
}
