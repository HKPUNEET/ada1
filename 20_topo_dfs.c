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
    stk[++top] = u; // push after all descendants visited
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
    FILE *fp = fopen("dfstopo.txt", "w");
    srand(time(NULL));

    for (n = 4; n <= 12; n++)
    {
        /* ---------- BEST CASE : empty graph (no edges) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = 0;

        for (int i = 0; i < n; i++)
            visited[i] = 0;
        top = -1;
        count = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i);
        int best = count;

        /* ---------- WORST CASE : complete DAG (all forward edges) ---------- */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = (i < j) ? 1 : 0;

        for (int i = 0; i < n; i++)
            visited[i] = 0;
        top = -1;
        count = 0;
        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i);
        int worst = count;

        fprintf(fp, "%d %d %d\n", n, best, worst);
    }
    fclose(fp);
    printf("Data written (n best worst).\n");
}

int main()
{
    int ch;
    printf("1.Tester 2.Plotter\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1)
        tester();
    else
        plotter();
}
