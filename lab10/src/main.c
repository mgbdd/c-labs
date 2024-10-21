#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define OUT_OF_MEMORY 0
#define BAD_INPUT 0

typedef struct Point Point;
struct Point
{
    int x, y;
};

double Rotate(Point a, Point b, Point c)
{
    return (((double)b.x - a.x) * ((double)c.y - b.y) - ((double)b.y - a.y) * ((double)c.x - b.x));
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void FindBottomPoint(Point points[], int listOfPoints[], int N)
{
    for (int i = 1; i < N; i++)
    {
        int bottomX = points[listOfPoints[0]].x;
        int bottomY = points[listOfPoints[0]].y;
        int currentX = points[listOfPoints[i]].x;
        int currentY = points[listOfPoints[i]].y;
        if ((currentX < bottomX) || (currentX == bottomX && currentY < bottomY))
        {
            Swap(listOfPoints + i, listOfPoints);
        }
    }
    listOfPoints[N] = listOfPoints[0];
}

void SortPoints(int listOfPoints[], Point points[], int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int left = first, right = last;
    Point lowest = points[listOfPoints[0]];
    Point middle = points[listOfPoints[(left + right) / 2]];

    do
    {
        while (1)
        {
            double r = Rotate(lowest, middle, points[listOfPoints[left]]); 
            if (r >= 0)
            {
                break;
            }
            left++;
        }
        while (Rotate(lowest, middle, points[listOfPoints[right]]) > 0)
        {
            right--;
        }

        if (left <= right)
        {
            Swap(listOfPoints + left, listOfPoints + right);
            left++;
            right--;
        }
    } while (left <= right);
    SortPoints(listOfPoints, points, first, right);
    SortPoints(listOfPoints, points, left, last);
}

void PrintPoints(Point points[], int size, int convexHull[])
{
    for (int i = 0; i < size; i++)
    {
        printf("%i %i\n", points[convexHull[i]].x, points[convexHull[i]].y);
    }
}

void GeneralCase(Point points[], int listOfPoints[], int convexHull[], int N, int *size)
{
    convexHull[0] = listOfPoints[0];
    convexHull[1] = listOfPoints[1];
    int j = 2;
    double rot;
    Point A, B, C;
    for (int i = 2; i <= N; i++)
    {
        while (j > 1)
        {
            A = points[convexHull[j - 2]];
            B = points[convexHull[j - 1]];
            C = points[listOfPoints[i]];
            rot = Rotate(A, B, C);
            if (rot > 0)
            {
                break;
            }
            j--;
        }
        convexHull[j] = listOfPoints[i];
        j++;
    }
    if (j > 2)
    {
        *size = j - 1;
    }
    else
    {
        *size = j;
    }
}

void OneLineCase(Point points[], int listOfPoints[], int convexHull[], int N, int *size)
{
    if (points[listOfPoints[0]].x == points[listOfPoints[N - 1]].x) 
    {
        double maxY = (double)points[listOfPoints[0]].y;
        int IndMaxY = 0;
        for (int i = 1; i < N; i++)
        {
            if (points[listOfPoints[i]].y > maxY)
            {
                maxY = points[listOfPoints[i]].y;
                IndMaxY = i;
            }
        }
        convexHull[0] = listOfPoints[0];
        *size = 2;
        convexHull[1] = listOfPoints[IndMaxY];
    }
    else 
    {
        double maxX = (double)points[listOfPoints[0]].x;
        int IndMaxX = 0;
        for (int i = 1; i < N; i++)
        {
            if (points[listOfPoints[i]].x > maxX)
            {
                maxX = points[listOfPoints[i]].x;
                IndMaxX = i;
            }
        }
        convexHull[0] = listOfPoints[0];
        convexHull[1] = listOfPoints[IndMaxX];
        *size = 2;
    }
}

void GrahamScan(Point points[], int listOfPoints[], int convexHull[], int N, int *size)
{
    if (N == 0)
    {
        return;
    }
    bool oneLineFlag = 1;
    for (int i = 0; i < N; i++)
    {
        convexHull[0] = listOfPoints[0];
        convexHull[1] = listOfPoints[1];
        int j = 2;
        if (Rotate(points[convexHull[j - 2]], points[convexHull[j - 1]], points[listOfPoints[i]]) != 0)
        {
            oneLineFlag = 0;
            break;
        }
    }
    if (oneLineFlag == 1)
        OneLineCase(points, listOfPoints, convexHull, N, size);
    else
        GeneralCase(points, listOfPoints, convexHull, N, size);
}

int main()
{
    int N;
    if (scanf("%i", &N) == EOF)
    {
        return BAD_INPUT;
    }

    if (N < 0 || N > 100000)
    {
        printf("bad number of points\n");
        return BAD_INPUT;
    }

    Point points[N];
    for (int i = 0; i < N; i++)
    {
        if (scanf("%i %i", &points[i].x, &points[i].y) != 2)
        {
            printf("bad number of lines\n");
            return BAD_INPUT;
        }
    }
    if (N == 1)
    {
        printf("%i %i\n", points[0].x, points[0].y);
        return 0;
    }
    int *listOfPoints = malloc((N + 1) * sizeof(int));
    if (listOfPoints == NULL)
    {
        perror("out of memmory");
        return OUT_OF_MEMORY;
    }
    for (int i = 0; i < N; i++)
    {
        listOfPoints[i] = i;
    }
    FindBottomPoint(points, listOfPoints, N);
    SortPoints(listOfPoints, points, 1, N - 1);
    int *convexHull = malloc((N + 1) * sizeof(int));
    if (convexHull == NULL)
    {
        perror("out of memmory");
        free(listOfPoints);
        return OUT_OF_MEMORY;
    }
    int size = 0;
    GrahamScan(points, listOfPoints, convexHull, N, &size);
    PrintPoints(points, size, convexHull);
    free(listOfPoints);
    free(convexHull);
}
