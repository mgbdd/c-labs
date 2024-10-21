#include "BTrees.h"

int main()
{
    FILE *Keys = fopen("in.txt", "r");
    int degree, keyNum;

    if (fscanf(Keys, "%i", &degree) == EOF || degree < 2 || degree > 2000)
    {
        fclose(Keys);
        perror("bad input");
        return BAD_INPUT;
    }

    if (fscanf(Keys, "%i", &keyNum) == EOF || keyNum > 2000000)
    {
        fclose(Keys);
        perror("bad input");
        return BAD_INPUT;
    }

    if (keyNum == 0)
    {
        printf("0\n");
        fclose(Keys);
        return BAD_INPUT;
    }

    BTree tree = {degree, 0, NULL};
    bool memFlag = 0;
    BNode *root = CreateBNode(&tree, &memFlag);
    if (memFlag == 1)
    {
        perror("memory allocation problem");
        fclose(Keys);
        return OUT_OF_MEMORY;
    }
    tree.root = root;
    int key;
    for (int i = 0; i < keyNum; i++)
    {
        if (fscanf(Keys, "%i", &key) == EOF)
        {
            DeleteTree(tree.root);
            fclose(Keys);
            perror("bad input");
            return BAD_INPUT;
        }
        InsertInTree(&tree, key, &memFlag);
        if (memFlag == 1)
        {
            perror("memory allocation problem");
            fclose(Keys);
            return OUT_OF_MEMORY;
        }
    }
    printf("%i\n", tree.height + 1);
    DeleteTree(tree.root);
    fclose(Keys);
}
