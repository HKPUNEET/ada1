#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int A[20][20], indeg[20], stk[20], result[20];
int n, top, count;

/* Kahn's algorithm: repeatedly remove 0-indegree (source) vertices */
void topoSort()
{
    top = -1;
    count = 0;
    int k = 0;
    for (int j = 0; j < n; j++)
    {
        indeg[j] = 0;
        for (int i = 0; i < n; i++)
        {
            indeg[j] += A[i][j];
            count++;
        }
    }
    for (int i = 0; i < n; i++)
        if (!indeg[i])
            stk[++top] = i;
    while (top != -1)
    {
        int u = stk[top--];
        result[k++] = u;
        for (int i = 0; i < n; i++)
        {
            count++;
            if (A[u][i] && --indeg[i] == 0)
                stk[++top] = i;
        }
    }
    printf("Topological Order: ");
    for (int i = 0; i < k; i++)
        printf("%d ", result[i]);
    printf("\n");
}

void tester()
{
    count = 0;
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    topoSort();
    printf("Count = %d\n", count);
}

void plotter()
{
    FILE *fp = fopen("topo.txt", "w");
    srand(time(NULL));
    for (n = 2; n <= 10; n++)
    {
        // Random DAG: edges only go from i to j where i < j
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = (i < j) ? rand() % 2 : 0;
        count = 0;
        topoSort();
        fprintf(fp, "%d %d\n", n, count);
    }
    fclose(fp);
    printf("Data written.\n");
}

int main()
{
    int ch;
    printf("1.Tester  2.Plotter\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1)
        tester();
    else
        plotter();
}
