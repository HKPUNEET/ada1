#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100], n, count;

/* Recursive DFS; prints vertex as letter (0=A, 1=B, ...) */
void dfs(int v)
{
    visited[v] = 1;
    count++;
    printf("%c ", v + 65);
    for (int i = 0; i < n; i++)
        if (graph[v][i] && !visited[i])
            dfs(i);
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }
    count = 0;
    printf("DFS: ");
    dfs(0);
    printf("\n%s\n", count == n ? "Connected" : "Not Connected");
}

void plotter()
{
    FILE *best = fopen("dfsbest.txt", "w"), *worst = fopen("dfsworst.txt", "w");
    for (int sz = 1; sz <= 10; sz++)
    {
        n = sz;
        // Best: chain graph 1-2-3-...-n
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;
        }
        for (int i = 0; i < n - 1; i++)
            graph[i][i + 1] = 1;
        count = 0;
        dfs(0);
        fprintf(best, "%d %d\n", n, count);
        // Worst: complete graph
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j);
        }
        count = 0;
        dfs(0);
        fprintf(worst, "%d %d\n", n, count);
    }
    fclose(best);
    fclose(worst);
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
