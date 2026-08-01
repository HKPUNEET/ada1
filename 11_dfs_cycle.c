#include <stdio.h>
#include <stdlib.h>

int graph[100][100], visited[100];
int n, count, cyclic, ops;

/* DFS with parent tracking to detect back-edges (cycles) */
void dfs(int v, int parent)
{
    visited[v] = 1;
    count++;
    for (int i = 0; i < n; i++)
    {
        ops++;
        if (i != parent && graph[v][i] && visited[i])
            cyclic = 1; // back edge = cycle
        if (graph[v][i] && !visited[i])
            dfs(i, v);
    }
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }
    count = cyclic = ops = 0;
    int components = 0;
    printf("DFS: ");
    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            dfs(i, -1);
            components++;
        }
    printf("\n%s | Components=%d | %s\n",
           count == n ? "Connected" : "Not Connected", components, cyclic ? "Cyclic" : "Acyclic");
}

void plotter()
{
    FILE *best = fopen("dfsbest.txt", "w"), *worst = fopen("dfsworst.txt", "w");
    for (int sz = 1; sz <= 10; sz++)
    {
        n = sz;
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;
        }
        for (int i = 0; i < n - 1; i++)
            graph[i][i + 1] = 1; // chain
        ops = count = cyclic = 0;
        dfs(0, -1);
        fprintf(best, "%d %d\n", n, ops);
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j);
        } // complete
        ops = count = cyclic = 0;
        dfs(0, -1);
        fprintf(worst, "%d %d\n", n, ops);
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
