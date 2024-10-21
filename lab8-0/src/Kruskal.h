#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
     short begin, end;
     int weight;
};

int CheckInputData(const int vertexNum, const int edgeNum);
void FillEdgesList(Edge *edges, const int edgeNum, const int vertexNum, int *errorFlag);
void Kruskal(Edge *edges, const int vertexNum, const int edgeNum, bool *memFlag, Edge *answers, int *spanningCount, bool *spanningTreeFlag);
void PrintSpanningTree(Edge *answers, const int spanningTreeCount);
