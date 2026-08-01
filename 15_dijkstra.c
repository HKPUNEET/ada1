#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int cost[20][20], dist[20], visited[20];
int n, count;

/* Greedy SSSP: O(n^2) with adjacency matrix */
void dijkstra(int src)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[src][i];
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;
    for (int k = 0; k < n - 1; k++)
    {
        int min = INT_MAX, u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        visited[u] = 1;
        for (int v = 0; v < n; v++)
        {
            count++;
            if (!visited[v] && dist[u] + cost[u][v] < dist[v])
                dist[v] = dist[u] + cost[u][v];
        }
    }
}

void tester()
{
    int src;
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (!cost[i][j] && i != j)
                cost[i][j] = INT_MAX; // 0 = no edge
        }
    printf("Source: ");
    scanf("%d", &src);
    count = 0;
    dijkstra(src);
    for (int i = 0; i < n; i++)
        if (i != src)
            printf("%d->%d = %d\n", src, i, dist[i]);
    printf("Operations = %d\n", count);
}

void plotter()
{
    FILE *fp = fopen("dijkstra.txt", "w");
    srand(time(NULL));
    for (n = 2; n <= 10; n++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] = (i == j) ? 0 : rand() % 20 + 1;
        count = 0;
        dijkstra(0);
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
