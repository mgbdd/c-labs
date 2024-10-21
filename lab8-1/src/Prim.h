#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

enum Errors
{
    OUT_OF_MEMORY = 0,
    BAD_INPUT = 0,
    BAD_NUMBER_OF_EDGES = 0,
    BAD_NUMBER_OF_VERTICES = 0,
    BAD_NUMBER_OF_LINES = 0,
    BAD_VERTEX = 0,
    BAD_LENGTH = 0,
    NO_SPANNING_TREE = 0
};


typedef struct Edge Edge;
struct Edge
{
    short x;
    short y;
};

int CheckInsertData(const int vertexNum, const int edgeNum);
int **CreateAdjMatrix(const int vertexNum);
void FillAdjMatrix(int **matrix, const int edgeNum, const int vertexNum, int *errorFlag);
long long int *CreateMinDistance(const int vertexNum);
Edge *Prim(long long int *minDistance, int **matrix, const int vertexNum);
bool CheckSpanningTree(Edge *MSTedges, const int vertexNum);
void PrintMST(const int vertexNum, Edge *MSTedges);
void DeleteMatrix(const int vertexNum, int **matrix);
