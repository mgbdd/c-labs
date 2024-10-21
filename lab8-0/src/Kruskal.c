#include "Kruskal.h"

int CheckInputData(const int vertexNum, const int edgeNum)
{
     if (vertexNum == 1 && edgeNum == 0)
     {
          return 1;
     }
     if (vertexNum == 0 || (edgeNum == 0 && vertexNum != 1))
     {
          printf("no spanning tree");
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

static int CompareWeight(const void *a, const void *b)
{
     return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

static void PutInRoot(const int vertexNum, int *parents)
{ 
     for (int i = 0; i < vertexNum; i++)
     {
          parents[i] = i;
     }
}

static int FindRoot(const int vertex, int *parents)
{
     if (parents[vertex] == vertex)
     {
          return vertex;
     }
     return parents[vertex] = FindRoot(parents[vertex], parents);
}

static void UniteTheTrees(int begin, int end, int *parents, int *rank)
{
     begin = FindRoot(begin, parents);
     end = FindRoot(end, parents);

     if (rank[begin] < rank[end])
     {
          parents[begin] = end;
     }
     else
     {
          parents[end] = begin;
          if (rank[begin] == rank[end])
          {
               rank[begin]++;
          }
     }
}

static void AddVerticeToSpanningTreeList(Edge toAdd, Edge *answers, int count)
{
     answers[count].begin = toAdd.begin;
     answers[count].end = toAdd.end;
}

void Kruskal(Edge *edges, const int vertexNum, const int edgeNum, bool *memFlag, Edge *answers, int *spanningCount, bool *spanningTreeFlag)
{
     int *parents = malloc(sizeof(int) * vertexNum);
     if (parents == NULL)
     {
          *memFlag = 1;
          return;
     }
     PutInRoot(vertexNum, parents);
     int *rank = calloc(sizeof(int), vertexNum);
     if (rank == NULL)
     {
          *memFlag = 1;
          free(parents);
          return;
     }

     int usedVertices = 1;
     int localCount = *spanningCount;
     for (int i = 0; i < edgeNum; i++)
     {
          int begin = edges[i].begin - 1;
          int end = edges[i].end - 1;
          if (FindRoot(begin, parents) != FindRoot(end, parents)) 
          {
               AddVerticeToSpanningTreeList(edges[i], answers, localCount); 
               localCount++;
               usedVertices++;
               UniteTheTrees(begin, end, parents, rank);
               if (usedVertices == vertexNum)
               {
                    break;
               }
          }
     }
     *spanningCount = localCount;
     if (usedVertices != vertexNum)
     {
          *spanningTreeFlag = 1;
          free(parents);
          free(rank);
          return;
     }
     free(parents);
     free(rank);
}

void FillEdgesList(Edge *edges, const int edgeNum, const int vertexNum, int *errorFlag)
{
     if (edges == NULL)
     {
          perror("memory allocation error");
          *errorFlag = 1;
          return;
     }
     short begin, end;
     int weight;

     for (int i = 0; i < edgeNum; i++) 
     {
          if (scanf("%hi %hi %i", &begin, &end, &weight) == EOF)
          {
               free(edges);
               printf("bad number of lines");
               *errorFlag = 2;
               return;
          }

          if (begin < 1 || begin > vertexNum || end < 1 || end > vertexNum)
          {
               free(edges);
               printf("bad vertex");
               *errorFlag = 3;
               return;
          }

          if (weight < 0 || weight > INT_MAX)
          {
               free(edges);
               printf("bad length");
               *errorFlag = 4;
               return;
          }

          edges[i].begin = begin;
          edges[i].end = end;
          edges[i].weight = weight;
     }

     qsort(edges, edgeNum, sizeof(Edge), CompareWeight); 
}

void PrintSpanningTree(Edge *answers, const int spanningTreeCount)
{
     for (int i = 0; i < spanningTreeCount; i++)
     {
          printf("%hi %hi\n", answers[i].begin, answers[i].end);
     }
}
