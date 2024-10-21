#include "Dijkstra.h"

static void SetValue(long long int *minElement, int *minIndex)
{
    *minElement = LLONG_MAX;
    *minIndex = INT_MAX;
}

static void ChangeMinDistance(long long int minElement, const int minIndex, long long int *minDistance, int *parent, const int vertexNum, int **matrix)
{
    for (int i = 0; i < vertexNum; i++)
    {
        if (matrix[minIndex][i] > 0)
        {
            long long int tmp = minElement + matrix[minIndex][i];
            if (tmp < minDistance[i])
            {
                minDistance[i] = tmp;
                parent[i] = minIndex + 1;
            }
        }
    }
}

static bool OverflowCheck(const int index, const int vertexNum, long long int *minDistance)
{
    if (minDistance[index] <= INT_MAX)
        return 0;
    int count = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        if (minDistance[i] >= INT_MAX && minDistance[i] != LLONG_MAX && i != index)
            count++;
    }
    if (count >= 2)
        return 1;
    return 0;
}

static void PrintPath(const int outputIndex, int *path)
{
    printf("\n");
    for (int i = 0; i < outputIndex; i++)
    {
        printf("%i ", path[i]);
    }
}

int CheckInput(const int vertexNum, const int edgesNum)
{
    if (vertexNum == 0 && edgesNum == 0)
    {
        printf("bad vertex");
        return 1;
    }
    if (vertexNum < 0 || vertexNum > 5000)
    {
        printf("bad number of vertices");
        return 2;
    }
    if (edgesNum < 0 || edgesNum > vertexNum * (vertexNum + 1) / 2)
    {
        printf("bad number of edges");
        return 3;
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

long long int *CreateMinDistances(const int vertexNum)
{
    long long *minDistance = malloc(vertexNum * sizeof(long long int));
    if (minDistance == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        minDistance[i] = LLONG_MAX;
    }
    return minDistance;
}

int *FillMinDistance(long long int *minDistance, const int index, const int vertexNum, int **matrix)
{
    int *usedVertices = calloc(vertexNum, sizeof(int));
    if (usedVertices == NULL)
    {
        return NULL;
    }
    int *parent = calloc(vertexNum, sizeof(int));
    if (parent == NULL)
    {
        free(usedVertices);
        return NULL;
    }
    minDistance[index - 1] = 0;
    int minIndex = 0;
    long long int minElement = 0;

    while (minIndex != INT_MAX)
    {
        SetValue(&minElement, &minIndex);
        for (int i = 0; i < vertexNum; i++)
        {
            if (usedVertices[i] == 0 && minDistance[i] < minElement)
            {
                minElement = minDistance[i];
                minIndex = i;
            }
        }
        if (minIndex != INT_MAX)
        {
            ChangeMinDistance(minElement, minIndex, minDistance, parent, vertexNum, matrix);
            usedVertices[minIndex] = 1;
        }
    }
    free(usedVertices);
    return parent;
}

void Dijkstra(const int vertexNum, const int finish, const int start, long long int *minDistance, int *parent, int *errorFlag)
{
    int *path = malloc(vertexNum * sizeof(vertexNum));
    if (path == NULL)
    {
        *errorFlag = 1;
        return;
    }
    int currentIndex = finish - 1;
    int outputIndex = 0;
    path[outputIndex++] = finish;

    if (OverflowCheck(finish - 1, vertexNum, minDistance) == 1)
    {
        printf("\noverflow");
        free(path);
        *errorFlag = 2;
        return;
    }
    if (minDistance[finish - 1] == LLONG_MAX)
    {
        printf("\nno path");
        free(path);
        *errorFlag = 3;
        return;
    }

    while (currentIndex != start - 1)
    {
        currentIndex = parent[currentIndex] - 1;
        path[outputIndex++] = currentIndex + 1;
    }
    PrintPath(outputIndex, path);
    free(path);
}

void PrintMinDistance(long long int *minDistance, const int vertexNum, const int index)
{
    for (int i = 0; i < vertexNum; i++)
    {
        if (minDistance[i] == LLONG_MAX)
        {
            printf("oo ");
        }
        else if (i == index)
        {
            printf("0 ");
        }
        else if (minDistance[i] > INT_MAX)
        {
            printf("INT_MAX+ ");
            ;
        }
        else
        {
            printf("%lld ", minDistance[i]);
        }
    }
}

void DeleteMatrix(const int vertexNum, int **matrix)
{
    for (int i = 0; i < vertexNum; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
