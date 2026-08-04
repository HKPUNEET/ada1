#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int graph[100][100], visited[100], q[100], parent[100];
int n, count, isCyclic;

/* 
   BFS that can optionally print the component.
   printFlag = 1 → prints vertices (for tester)
   printFlag = 0 → silent (for plotter)
*/
void bfs(int src, int printFlag)
{
    int f = 0, r = -1;
    visited[src] = 1;
    parent[src] = -1;
    q[++r] = src;

    while (f <= r)
    {
        int u = q[f++];
        if (printFlag)
            printf("%d ", u);

        for (int v = 0; v < n; v++)
        {
            count++;
            if (graph[u][v])
            {
                if (!visited[v])
                {
                    visited[v] = 1;
                    parent[v] = u;
                    q[++r] = v;
                }
                else if (v != parent[u])
                {
                    isCyclic = 1;
                }
            }
        }
    }
}

void analyseGraph()
{
    int components = 0;
    isCyclic = 0;

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    count = 0;
    printf("\nConnected Components:\n");

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            components++;
            printf("Component %d: ", components);
            bfs(i, 1);          // printFlag = 1
            printf("\n");
        }
    }

    if (components == 1)
        printf("Graph is CONNECTED\n");
    else
        printf("Graph is NOT CONNECTED (%d components)\n", components);

    if (isCyclic)
        printf("Graph contains CYCLE(S)\n");
    else
        printf("Graph is ACYCLIC\n");

    printf("Total operations = %d\n", count);
}

void tester()
{
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    analyseGraph();
}

void plotter()
{
    FILE *fp = fopen("bfs.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (n = 2; n <= 10; n++)
    {
        /* ---------- BEST CASE : sparse graph (path) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
        {
            graph[i][i + 1] = 1;
            graph[i + 1][i] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            parent[i] = -1;
        }
        count = 0;
        isCyclic = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                bfs(i, 0);          // silent
        int best = count;

        /* ---------- WORST CASE : complete graph ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j) ? 1 : 0;

        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            parent[i] = -1;
        }
        count = 0;
        isCyclic = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                bfs(i, 0);          // silent
        int worst = count;

        fprintf(fp, "%d %d %d\n", n, best, worst);
    }
    fclose(fp);
    printf("Data written to bfs.txt (n best worst)\n");
}

int main()
{
    int ch;
    printf("1.Tester  2.Plotter\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1)
        tester();
    else if (ch == 2)
        plotter();
    else
        printf("Invalid choice\n");

    return 0;
}
