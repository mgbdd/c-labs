#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

enum Errors
{
    OUT_OF_MEMORY = 0,
    BAD_NUMBER_OF_VERTICES = 0,
    BAD_NUMBER_OF_EDGES = 0,
    BAD_VERTEX = 0,
    BAD_LENGTH = 0,
    BAD_NUMBER_OF_LINES = 0,
    BAD_INPUT = 0,
    NO_PATH = 0,
    OVERFLOW = 0
};

int CheckInput(const int vertexNum, const int edgesNum);
int **CreateAdjMatrix(const int vertexNum);
void FillAdjMatrix(int **matrix, const int edgeNum, const int vertexNum, int *errorFlag);
long long int *CreateMinDistances(const int vertexNum);
int *FillMinDistance(long long int *minDistance, const int index, const int vertexNum, int **matrix);
void PrintMinDistance(long long int *minDistance, const int vertexNum, const int index);
void Dijkstra(const int vertexNum, const int finish, const int start, long long int *minDistance, int *parent, int *errorFlag);
void DeleteMatrix(const int vertexNum, int **matrix);
