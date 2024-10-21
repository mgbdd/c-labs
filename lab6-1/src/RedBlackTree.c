#include "RedBlackTree.h"

int ColorCheck(Node *root)
{
    if (root == NULL)
        return 0;
    switch (root->color)
    {
        case RED:
            return 1;
        case BLACK:
            return 0;
        default:
            return 1;
    }
}

void ColorFix(Node *root)
{
    root->color = !root->color;
    root->leftChild->color = !root->leftChild->color;
    root->rightChild->color = !root->rightChild->color;
}

Node *LeftRotation(Node *root) 
{
    Node *tmp = root->rightChild;
    root->rightChild = tmp->leftChild;
    tmp->leftChild = root;
    tmp->color = root->color;
    root->color = RED;
    return tmp;
}

Node *RightRotation(Node *root)
{
    Node *tmp = root->leftChild;
    root->leftChild = tmp->rightChild;
    tmp->rightChild = root;
    tmp->color = root->color;
    root->color = RED;
    return tmp;
}

Node *LeftRightRotation(Node *root) 
{
    root->rightChild = RightRotation(root->rightChild); 
    return LeftRotation(root);
}

Node *RightLeftRotation(Node *root) 
{
    root->leftChild = LeftRotation(root->leftChild);
    return RightRotation(root);
}

Node *LeftBalance(Node *root)  
{
    if (ColorCheck(root->leftChild) == 1) 
    {
        if (ColorCheck(root->rightChild) == 1)
        {                                         
            if (ColorCheck(root->leftChild->leftChild) == 1 || ColorCheck(root->leftChild->rightChild) == 1)
            {
                ColorFix(root);
            }
        }
        else
        {
            if (ColorCheck(root->leftChild->leftChild) == 1) 
            {
                root = RightRotation(root);
            }
            else if (ColorCheck(root->leftChild->rightChild) == 1) 
            {
                root = RightLeftRotation(root);   
            }
        }
    }
    return root;
}

Node *RightBalance(Node *root)  
{
    if (ColorCheck(root->rightChild) == 1) 
    {
        if (ColorCheck(root->leftChild) == 1) 
        {                                       
            if (ColorCheck(root->rightChild->rightChild) == 1 || ColorCheck(root->rightChild->leftChild) == 1)
            {
                ColorFix(root);
            }
        }
        else
        {
            if (ColorCheck(root->rightChild->rightChild) == 1) 
            {
                root = LeftRotation(root);
            }
            else if (ColorCheck(root->rightChild->leftChild) == 1)
            {
                root = LeftRightRotation(root);
            }
        }
    }
    return root;
}

Node *InsertNode(Node *root, Node *tmp, int key)
{
    if (root == NULL)
    {
        tmp->key = key;
        tmp->color = RED;
        tmp->leftChild = NULL;
        tmp->rightChild = NULL;
        root = tmp;
        return root;
    }
    if (key > root->key)
    {
        root->rightChild = InsertNode(root->rightChild, tmp, key);
        return RightBalance(root);
    }
    else 
    {
        root->leftChild = InsertNode(root->leftChild, tmp, key);
        return LeftBalance(root);
    }
}

int CalcHeight(Node *root)
{
    int h = 0;
    Node *tmp = root;
    while (1)
    {
        if (tmp->color == BLACK)
            {h++;}
        tmp = tmp->rightChild;
        if (tmp == NULL)
        {
            h++;
            break;
        }
    }
    return h;
}


