#include "RedBlackTree.h"


int main()
{
    FILE *Keys = fopen("in.txt", "r");
    int N;
    if (fscanf(Keys, "%i", &N) == EOF)
    {
        fclose(Keys);
        return BAD_INPUT;
    }
    if (N == 0)
    {
        fprintf(stdout, "0");
        fclose(Keys);
        return BAD_INPUT;
    }

    Node *root = NULL;
    Node *nodesArr = malloc(N * sizeof(Node));
    if (nodesArr == NULL)
    {
        perror("out of memmory");
        fclose(Keys);
        return OUT_OF_MEMMORY;
    }
    int key;
    for (int i = 0; i < N; i++)
    {
        if (fscanf(Keys, "%i", &key) == EOF)
        {
           free(nodesArr);
           fclose(Keys);
           return BAD_INPUT;
        }
        Node* new = &nodesArr[i];
        root = InsertNode(root, new, key);
        root->color = BLACK;
    }
    printf("%i\n", CalcHeight(root));
    free(nodesArr);
    fclose(Keys);
}
