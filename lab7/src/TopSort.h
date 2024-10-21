#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum Errors
{
    OUT_OF_MEMORY = 0,
    BAD_NUMBER_OF_VERTICES = 0,
    BAD_NUMBER_OF_EDGES = 0,
    BAD_VERTEX = 0,
    BAD_NUMBER_OF_LINES = 0,
    IMPOSSIBLE_TO_SORT = 0    
};

enum Colors
{
    GREY = 1,
    BLACK = 2
};

void FillAdjacencyMatrix(const int N, const int M, bool *errorFlag, char *graph, const int matrixBytes);
void DFS(const int N, char visitedVertices[], char graph[], bool *cycleFlag, int matrixBytes, int **stackPointer, const int currPos);
void Toposort(const int N, char visitedVertices[], char graph[], bool *cycleFlag, int matrixBytes, int **stackPointer);
