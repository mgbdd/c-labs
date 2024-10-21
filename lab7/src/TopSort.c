#include "TopSort.h"

void FillAdjacencyMatrix(int N, int M, bool *errorFlag, char *graph, int matrixBytes)
{
	int start, end;
    for (int i = 0; i < M; i++) 
    {
        if (scanf("%i %i", &start, &end) != 2)
        {
            printf("bad number of lines");
			*errorFlag = 1;
            return;
        }
        if (start < 1 || start > N || end < 1 || end > N)
        {
            printf("bad vertex");
			*errorFlag = 1;
            return;
        }

        int lineIndex = (start - 1) * matrixBytes + (end - 1)/8;
        char binaryMask = 128 >> (end - 1) % 8;
        graph[lineIndex] |= binaryMask;
    }
}

void DFS(int N, char visitedVertices[], char graph[], bool *cycleFlag, int matrixBytes, int **stackPointer, int currPos)
{
    visitedVertices[currPos] = GREY;
    for (int i = 0; i < N; i++)
    {
        if (graph[currPos * matrixBytes + i / 8] & (128 >> (i % 8))) 
        {
            if (visitedVertices[i] == 1)
			{
                *cycleFlag = 1;
				return;
			}
            if (visitedVertices[i] == 0) 
            {
                DFS(N, visitedVertices, graph, cycleFlag, matrixBytes, stackPointer, i);
            }
        }
    }
    visitedVertices[currPos] = BLACK;
    *(*stackPointer) = currPos + 1;
    (*stackPointer)++;
}

void Toposort(int N, char visitedVertices[], char graph[], bool *cycleFlag, int matrixBytes, int **stackPointer)
{
	for (int i = 0; i < N; i++)
    {
        if (visitedVertices[i] == 0)
        {
            DFS(N, visitedVertices, graph, cycleFlag, matrixBytes, stackPointer, i);
			if (*cycleFlag == 1)
			{
				return;
			}
        }
    }
}
