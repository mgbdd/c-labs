#include "Prim.h"

int main()
{
    int vertexNum, edgeNum;
    if (scanf("%i %i", &vertexNum, &edgeNum) == EOF)
    {
        perror("scanf error");
        return BAD_INPUT;
    }
    int errorFlag = CheckInsertData(vertexNum, edgeNum);
    switch (errorFlag)
    {
    case 1:
        return NO_SPANNING_TREE;
    case 2:
        return BAD_INPUT;
    case 3:
        return BAD_NUMBER_OF_VERTICES;
    case 4:
        return BAD_NUMBER_OF_EDGES;
    default:
        errorFlag = 0;
    }
    int **adjMatrix = CreateAdjMatrix(vertexNum);
    if (adjMatrix == NULL)
    {
        perror("memory wasn't allocated");
        return OUT_OF_MEMORY;
    }
    FillAdjMatrix(adjMatrix, edgeNum, vertexNum, &errorFlag);
    switch (errorFlag)
    {
    case 1:
        DeleteMatrix(vertexNum, adjMatrix);
        return BAD_NUMBER_OF_LINES;
    case 2:
        DeleteMatrix(vertexNum, adjMatrix);
        return BAD_VERTEX;
    case 3:
        DeleteMatrix(vertexNum, adjMatrix);
        return BAD_LENGTH;
    default:
        break;
    }

    long long int *minDistance = CreateMinDistance(vertexNum);
    if (minDistance == NULL)
    {
        perror("memory wasn't allocated");
        DeleteMatrix(vertexNum, adjMatrix);
        return OUT_OF_MEMORY;
    }

    Edge *MST = Prim(minDistance, adjMatrix, vertexNum);
    if (MST == NULL)
    {
        free(minDistance);
        DeleteMatrix(vertexNum, adjMatrix);
        return OUT_OF_MEMORY;
    }

    if (!CheckSpanningTree(MST, vertexNum))
    {
        free(minDistance);
        DeleteMatrix(vertexNum, adjMatrix);
        free(MST);
        return NO_SPANNING_TREE;
    }
    PrintMST(vertexNum, MST);
    free(MST);
    free(minDistance);
    DeleteMatrix(vertexNum, adjMatrix);
}
