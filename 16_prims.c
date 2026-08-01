#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int cost[20][20], visited[20];
int n, count;

/* Greedy MST: pick minimum edge from visited set each step */
void prim()
{
    int minCost = 0;
    visited[0] = 1;
    printf("MST Edges:\n");
    for (int k = 0; k < n - 1; k++)
    {
        int mn = INT_MAX, u = -1, v = -1;
        for (int i = 0; i < n; i++)
            if (visited[i])
                for (int j = 0; j < n; j++)
                {
                    count++;
                    if (!visited[j] && cost[i][j] < mn)
                    {
                        mn = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
        visited[v] = 1;
        printf("%c-%c = %d\n", u + 65, v + 65, mn);
        minCost += mn;
    }
    printf("Total Cost = %d | Operations = %d\n", minCost, count);
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (!cost[i][j])
                cost[i][j] = INT_MAX;
        }
    }
    count = 0;
    prim();
}

void plotter()
{
    FILE *fp = fopen("prims.txt", "w");
    srand(time(NULL));
    for (n = 2; n <= 10; n++)
    {
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
                cost[i][j] = (i == j) ? 0 : rand() % 20 + 1;
        }
        count = 0;
        prim();
        fprintf(fp, "%d %d\n", n, count);
    }
    fclose(fp);
    printf("Data written.\n");
}

int main()
{
    int ch;
    while (1)
    {
        printf("\n1.Tester  2.Plotter  0.Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 0)
            break;
        if (ch == 1)
            tester();
        else
            plotter();
    }
}
