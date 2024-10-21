#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum Errors
{
    OUT_OF_MEMORY  = 101, 
    BAD_INPUT = 0
};

typedef struct BNode BNode;
struct BNode
{
    int keysNum;
    bool leaf;
    int *keys;
    BNode **children;
};

typedef struct BTree BTree;
struct BTree
{
    int degree;
    int height;
    BNode *root;
};

BNode *CreateBNode(BTree *tree, bool *memFlag);
void InsertInTree(BTree *tree, int key, bool *memFlag);
void DeleteTree(BNode *root);
