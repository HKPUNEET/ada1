#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int graph[100][100], visited[100], parent[100];
int n, count;

/* DFS with parent tracking for cycle detection */
void dfs(int u)
{
    visited[u] = 1;
    for (int v = 0; v < n; v++)
    {
        count++;                       // every matrix access is counted
        if (graph[u][v])
        {
            if (!visited[v])
            {
                parent[v] = u;
                dfs(v);
            }
            else if (v != parent[u])   // back edge → cycle
            {
                // cycle flag will be set in analyseGraph
            }
        }
    }
}

/* Check connectivity + acyclicity and print connected components */
void analyseGraph()
{
    int components = 0;
    int isCyclic = 0;

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

            /* collect the component while doing DFS */
            int stack[100], top = -1;
            visited[i] = 1;
            parent[i] = -1;
            stack[++top] = i;

            while (top >= 0)
            {
                int u = stack[top--];
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
                            stack[++top] = v;
                        }
                        else if (v != parent[u])
                        {
                            isCyclic = 1;
                        }
                    }
                }
            }
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
    FILE *fp = fopen("dfs.txt", "w");
    srand(time(NULL));

    for (n = 2; n <= 10; n++)
    {
        /* ---------- BEST CASE : sparse graph (a simple path) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;

        for (int i = 0; i < n - 1; i++)          // path 0-1-2-...-(n-1)
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
        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i);
        int best = count;

        /* ---------- WORST CASE : dense graph (complete graph) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j) ? 1 : 0;

        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            parent[i] = -1;
        }
        count = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i);
        int worst = count;

        fprintf(fp, "%d %d %d\n", n, best, worst);
    }
    fclose(fp);
    printf("Data written to dfs.txt (n best worst)\n");
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
    return 0;
}
