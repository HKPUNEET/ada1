#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int graph[100][100], visited[100], q[100];
int n, count;

void bfs(int src)
{
    int f = 0, r = -1, u, v;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[src] = 1;
    q[++r] = src;
    while (f <= r)
    {
        u = q[f++];
        printf("%d ", u);
        for (v = 0; v < n; v++)
        {
            count++;
            if (graph[u][v] && !visited[v])
            {
                visited[v] = 1;
                q[++r] = v;
            }
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
            scanf("%d", &graph[i][j]);
    printf("Enter source: ");
    scanf("%d", &src);
    count = 0;
    printf("BFS: ");
    bfs(src);
    printf("\nOperations = %d\n", count);
}

void plotter()
{
    FILE *fp = fopen("bfs.txt", "w");
    srand(time(NULL));
    for (n = 2; n <= 10; n++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j) ? rand() % 2 : 0;
        count = 0;
        bfs(0);
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
