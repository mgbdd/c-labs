#include "Kruskal.h"


int main()
{
     int vertexNum, edgeNum;
     if (scanf("%i %i", &vertexNum, &edgeNum) != 2)
     {
          perror("scanf error");
          return BAD_INPUT;
     }

     int errorFlag = CheckInputData(vertexNum, edgeNum);
     switch (errorFlag)
     {
     case 1:
          return BAD_INPUT;
     case 2:
          return NO_SPANNING_TREE;
     case 3:
          return BAD_NUMBER_OF_VERTICES;
     case 4:
          return BAD_NUMBER_OF_EDGES;
     default:
          break;
     }

     Edge *edges = calloc(edgeNum, sizeof(Edge));
     FillEdgesList(edges, edgeNum, vertexNum, &errorFlag);
     switch (errorFlag)
     {
     case 1:
          return OUT_OF_MEMORY;
     case 2:
          return BAD_NUMBER_OF_LINES;
     case 3:
          return BAD_VERTEX;
     case 4:
          return BAD_LENGTH;
     default:
          break;
     }

     bool memFlag = 0;
     Edge *answers = calloc(edgeNum, sizeof(Edge));
     if (answers == NULL)
     {
          perror("memory allocation error");
          free(edges);
          return OUT_OF_MEMORY;
     }

     bool spanningTreeFlag = 0;
     int spanningTreeCount = 0;
     Kruskal(edges, vertexNum, edgeNum, &memFlag, answers, &spanningTreeCount, &spanningTreeFlag);

     if (spanningTreeFlag == 1)
     {
          if (memFlag == 1)
          {
               perror("memory allocation error");
               free(answers);
               free(edges);
               return OUT_OF_MEMORY;
          }
          free(edges);
          free(answers);
          printf("no spanning tree");
          return NO_SPANNING_TREE;
     }
     PrintSpanningTree(answers, spanningTreeCount);
     free(edges);
     free(answers);
}
