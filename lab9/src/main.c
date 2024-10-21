#include "Dijkstra.h"

int main()
{
    int vertexNum, start, finish, edgesNum;
    if (scanf("%i %i %i %i", &vertexNum, &start, &finish, &edgesNum) != 4)
    {
        perror("scanf error");
        return BAD_INPUT;
    }
    int errorFlag = CheckInput(vertexNum, edgesNum);
    switch (errorFlag)
    {
    case 1:
        return BAD_VERTEX;
    case 2:
        return BAD_NUMBER_OF_VERTICES;
    case 3:
        return BAD_NUMBER_OF_EDGES;
    default:
        break;
    };
    int **adjMatrix = CreateAdjMatrix(vertexNum);
    if (adjMatrix == NULL)
    {
        perror("memory wasn't allocated");
        return OUT_OF_MEMORY;
    }
    FillAdjMatrix(adjMatrix, edgesNum, vertexNum, &errorFlag);
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

    long long int *minDistance = CreateMinDistances(vertexNum);
    if (minDistance == NULL)
    {
        perror("memory wasn't allocated");
        DeleteMatrix(vertexNum, adjMatrix);
        return OUT_OF_MEMORY;
    }
    int *parent = FillMinDistance(minDistance, start, vertexNum, adjMatrix);
    if (parent == NULL)
    {
        DeleteMatrix(vertexNum, adjMatrix);
        free(minDistance);
        perror("memory wasn't allocated");
        return OUT_OF_MEMORY;
    }

    PrintMinDistance(minDistance, vertexNum, start - 1);
    Dijkstra(vertexNum, finish, start, minDistance, parent, &errorFlag);
    switch (errorFlag)
    {
    case 1:
        perror("memory wasn't allocated");
        DeleteMatrix(vertexNum, adjMatrix);
        free(minDistance);
        free(parent);
        return OUT_OF_MEMORY;
    case 2:
        DeleteMatrix(vertexNum, adjMatrix);
        free(minDistance);
        free(parent);
        return OVERFLOW;
    case 3:
        DeleteMatrix(vertexNum, adjMatrix);
        free(minDistance);
        free(parent);
        return NO_PATH;
    default:
        DeleteMatrix(vertexNum, adjMatrix);
        free(minDistance);
        free(parent);
    }
}
