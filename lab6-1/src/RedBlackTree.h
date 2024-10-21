#include <stdlib.h>
#include <stdio.h>

enum Colors
{
    RED = 0,
    BLACK = 1
};

enum Errors
{
    OUT_OF_MEMMORY = 101,
    BAD_INPUT = 0
};

typedef struct Node Node;
struct Node
{
    int key;
    int color;
    Node *leftChild;
    Node *rightChild;
};


int ColorCheck(Node *root);
void ColorFix(Node *root);
Node *LeftRotation(Node *root);
Node *RightRotation(Node *root);
Node *LeftRightRotation(Node *root);
Node *RightLeftRotation(Node *root);
Node *LeftBalance(Node *root);
Node *RightBalance(Node *root);
Node *InsertNode(Node *root, Node *tmp, int key);
int CalcHeight(Node *root);

