#include "TopSort.h"

int main() 
{
    int N, M;
    if (scanf("%i", &N) == EOF)
    {
        printf("bad number of lines");
        perror("bad number of lines");
        return BAD_NUMBER_OF_LINES;
    }
    if (N < 0 || N > 2000)
    {
        printf("bad number of vertices");
        perror("bad number of vertices");
        return BAD_NUMBER_OF_VERTICES;
    }
    if (scanf("%i", &M) == EOF)
    {
        printf("bad number of lines");
        perror("bad number of lines");
        return BAD_NUMBER_OF_LINES;
    }
    if (M < 0 || M > N * (N + 1) / 2)
    {
        printf("bad number of edges");
        perror("bad number of edges");
        return BAD_NUMBER_OF_EDGES;
    }
    int matrixBytes = (N + 7) / 8;
    char *graph = calloc(matrixBytes * N, sizeof(char));
    if (graph == NULL)
    {
        perror("memory wasn't allocated");
        return  OUT_OF_MEMORY;
    }

	bool errorFlag = 0;
	FillAdjacencyMatrix(N, M, &errorFlag, graph, matrixBytes);
	if (errorFlag == 1)
	{
		perror("scanf error in topological sort");
		free(graph);
		return BAD_VERTEX;
	}

    int *sortResult = calloc(N, sizeof(int));
    if (sortResult == NULL)
    {
        perror("memory wasn't allocated");
        free(graph);
        return OUT_OF_MEMORY;
    }
    int* stack = sortResult;
	int** stackPointer = &stack;


    char *visitedVertices = calloc(N, sizeof(char));
    if (visitedVertices == NULL)
    {
        free(sortResult);
        free(graph);
        perror("memory wasn't allocated");
        return OUT_OF_MEMORY;
    }
    
    bool cycleFlag = 0;
    
	Toposort(N, visitedVertices, graph, &cycleFlag, matrixBytes, stackPointer);

    if (cycleFlag == 1)
    {
        printf("impossible to sort");
        perror("cycle was detected");
        free(visitedVertices);
        free(sortResult);
        free(graph);
        return IMPOSSIBLE_TO_SORT;
    }
    
    while (stack != sortResult)
	{
		stack--;
		printf("%d ", *stack);
	}
    free(visitedVertices);
    free(sortResult);
    free(graph);   
}
