#include <stdlib.h>
#include <stdio.h>
#define MAX(a, b)  ((a) > (b)) ? (a) : (b)
#define OUT_OF_MEMORY 101
#define BAD_INPUT 102

void FillProfitTable(int N, int W, int *profitTab[], const int profit[], const int weight[])
{
    for (int line = 0; line <= N; line++)
    {
        for (int column = 0; column <= W; column++)
        {
            if (line == 0 || column == 0)
            {
                profitTab[line][column] = 0;
                continue;
            }
            if (column - weight[line - 1] < 0)
            {
                profitTab[line][column] = profitTab[line - 1][column];
            }
            else
            {
               profitTab[line][column] = MAX(profitTab[line - 1][column], profitTab[line - 1][column - weight[line - 1]] + profit[line - 1]);
            }
        }
    }
}

void GetListOfItems(int N, int W, const int profit[], const int weight[], int items[])
{
    int **profitTab = malloc((N + 1) * sizeof(int *));
    if (profitTab == NULL)
    {
        exit(OUT_OF_MEMORY);
    }
    for (int i = 0; i <= N; i++)
    {
        profitTab[i] = malloc((W + 1) * sizeof(int));
        if (profitTab[i] == NULL)
        {
            exit(OUT_OF_MEMORY);
        }
    }
    FillProfitTable(N, W, profitTab, profit, weight);
    printf("%i\n", profitTab[N][W]);
    int itemsCount = 1;
    for (int line = N; line > 0; line--)
    {
        if (profitTab[line][W] != profitTab[line - 1][W])
        {
            items[itemsCount] = line;
            itemsCount++;
            W = W - weight[line - 1];
        }
    }
    items[0] = itemsCount;
    for (int i = 0; i <= N; i++)
    {
        free(profitTab[i]);
    }
    free(profitTab);
}

int main()
{
    int N, W;
    if (scanf("%i %i", &N, &W) != 2)
    {
        exit(BAD_INPUT);
    }
    int *profit = malloc(N * sizeof(int));
    int *weight = malloc(N * sizeof(int));
    if (profit == NULL || weight == NULL)
    {
        exit(OUT_OF_MEMORY);
    }

    for (int i = 0; i < N; i++)
    {
        if (!scanf("%i %i", &weight[i], &profit[i]))
        {
            exit(BAD_INPUT);
        }
    }
    int *items = malloc(sizeof(int) * (N + 1));
    if (items == NULL)
    {
        exit(OUT_OF_MEMORY);
    }
    GetListOfItems(N, W, profit, weight, items);
    for (int i = items[0] - 1; i > 0; i--)
    {
        printf("%i %i\n", weight[items[i] - 1], profit[items[i] - 1]);
    }
    free(weight);
    free(profit);
    free(items);
}
