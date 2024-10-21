#include "Prim.h"

int CheckInsertData(const int vertexNum, const int edgeNum)
{
    if (vertexNum == 0 && edgeNum == 0)
    {
        printf("no spanning tree");
        return 1;
    }
    if (vertexNum == 1 && edgeNum == 0)
    {
        return 2;
    }
    if (vertexNum < 0 || vertexNum > 5000)
    {
        printf("bad number of vertices");
        return 3;
    }

    if (edgeNum < 0 || edgeNum > vertexNum * (vertexNum + 1) / 2)
    {
        printf("bad number of edges");
        return 4;
    }
    return 0;
}

int **CreateAdjMatrix(const int vertexNum)
{
    int **matrix = calloc(vertexNum, sizeof(int *));
    if (matrix == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        matrix[i] = calloc(vertexNum, sizeof(int));
        if (matrix[i] == NULL)
        {
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void FillAdjMatrix(int **matrix, const int edgeNum, const int vertexNum, int *errorFlag)
{
    for (int i = 0; i < edgeNum; i++)
    {
        int begin, end, weight;
        if (scanf("%i %i %i", &begin, &end, &weight) == EOF)
        {
            printf("bad number of lines");
            *errorFlag = 1;
            return;
        }

        if (begin < 1 || begin > vertexNum || end < 0 || end > vertexNum)
        {
            printf("bad vertex");
            *errorFlag = 1;
            return;
        }

        if (weight < 0 || weight > INT_MAX)
        {
            printf("bad length");
            *errorFlag = 2;
            return;
        } 

        matrix[begin - 1][end - 1] = weight;
		matrix[end - 1][begin - 1] = weight;
    }
}

long long int *CreateMinDistance(const int vertexNum)
{
	long long int *minDistance = malloc(vertexNum * sizeof(long long int));
    if(minDistance == NULL)
    {
        return NULL;
    }
	for (int i = 0; i < vertexNum; i++)
	{
		minDistance[i] = LLONG_MAX;
	}
	return minDistance;
}

static void SetValue(long long int *minEdge, int *minIndex)
{
	*minEdge = LLONG_MAX;
	*minIndex = INT_MAX;
}

static void ChangeMinDistance(const int minIndex, int **matrix,long long int *minDistance, const int vertexNum, Edge *MSTEdges, bool *usedVertices)
{
	for (int i = 0; i < vertexNum; i++)
	{
		if (usedVertices[i] == 0 && matrix[minIndex][i] > 0) 
		{
			long long int tmp = matrix[minIndex][i];
			if (tmp < minDistance[i])
			{
				minDistance[i] = tmp;
                MSTEdges[i].x = (short)(i + 1);
                MSTEdges[i].y =(short)(minIndex + 1);
			}
		}
    }
}

Edge *Prim(long long int *minDistance, int **matrix, const int vertexNum)
{
	bool *usedVertices = calloc(vertexNum, sizeof(bool));
    if(usedVertices == NULL)
    {
        return NULL;
    }

    Edge *MSTEdges = calloc(vertexNum, sizeof(Edge));
    if(MSTEdges == NULL)
    {
        free(usedVertices);
        return NULL;
    }
	minDistance[0] = 0;
	int minIndex = 0; 
	long long int minEdge = 0; 

	while (minIndex != INT_MAX)
	{
		SetValue(&minEdge, &minIndex);
		for (int i = 0; i < vertexNum; i++)
		{
			if (usedVertices[i] == 0 && minDistance[i] < minEdge)
			{
				minEdge = minDistance[i];
				minIndex = i;
			}
		}
		if (minIndex != INT_MAX)
		{
			ChangeMinDistance(minIndex, matrix, minDistance, vertexNum, MSTEdges, usedVertices);
			usedVertices[minIndex] = 1;
		}
	}
	free(usedVertices);
	return MSTEdges;
}

bool CheckSpanningTree(Edge *MSTEdges, const int vertexNum)
{
	int noSpanningTree = 0;
	for (int i = 0; i < vertexNum; i++)
	{
		if (MSTEdges[i].x == 0 && MSTEdges[i].y == 0)
		{
			noSpanningTree++;
		}
	}
	if (noSpanningTree != 1)
	{
		printf("no spanning tree");
		return 0;
	}
	return 1;
}

void PrintMST(const int vertexNum, Edge *MSTEdges)
{
	for (int i = 0; i < vertexNum; i++)
	{
        if ( MSTEdges[i].x != 0 && MSTEdges[i].y != 0)
        {
            printf("%hi %hi\n", MSTEdges[i].x, MSTEdges[i].y); 
        }	
	}
}

void DeleteMatrix(const int vertexNum, int **matrix)
{
    for(int i = 0; i < vertexNum; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
