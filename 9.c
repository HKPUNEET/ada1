#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int A[20][20], visited[20], stk[20];
int n, top, count;

/* Post-order DFS push gives reverse topological order */
void dfs(int u)
{
    visited[u] = 1;
    for (int v = 0; v < n; v++)
    {
        count++;
        if (A[u][v] && !visited[v])
            dfs(v);
    }
    stk[++top] = u;
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    for (int i = 0; i < n; i++)
        visited[i] = 0;
    top = -1;
    count = 0;

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i);

    printf("Topological Order: ");
    for (int i = top; i >= 0; i--)
        printf("%c ", stk[i] + 65);
    printf("\nCount = %d\n", count);
}

void plotter()
{
    FILE *best = fopen("dfstopo_best.txt", "w");
    FILE *worst = fopen("dfstopo_worst.txt", "w");

    for (n = 4; n <= 12; n++)
    {
        /* ---------- BEST CASE : sparse (path) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = 0;
        for (int i = 0; i < n - 1; i++)
            A[i][i + 1] = 1;          // 0→1→2→...→(n-1)

        for (int i = 0; i < n; i++) visited[i] = 0;
        top = -1; count = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i]) dfs(i);
        fprintf(best, "%d %d\n", n, count);

        /* ---------- WORST CASE : dense DAG (all forward edges) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = (i < j) ? 1 : 0;

        for (int i = 0; i < n; i++) visited[i] = 0;
        top = -1; count = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i]) dfs(i);
        fprintf(worst, "%d %d\n", n, count);
    }

    fclose(best);
    fclose(worst);
    printf("Data written to dfstopo_best.txt and dfstopo_worst.txt\n");
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
