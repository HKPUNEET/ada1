#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int graph[100][100], n, count;

/* Warshall: O(n^3) — fills transitive closure in-place */
void warshall()
{
    count = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (graph[i][k])
                for (int j = 0; j < n; j++)
                {
                    count++;
                    graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
                }
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    count = 0;
    warshall();
    printf("Transitive Closure:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
    printf("Operations = %d\n", count);
}

void plotter()
{
    FILE *best = fopen("warshall_best.txt", "w"), *worst = fopen("warshall_worst.txt", "w");
    for (int sz = 1; sz <= 10; sz++)
    {
        n = sz;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;
        for (int i = 0; i < n - 1; i++)
            graph[i][i + 1] = 1; // chain (best)
        count = 0;
        warshall();
        fprintf(best, "%d %d\n", n, count);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = (i != j); // complete (worst)
        count = 0;
        warshall();
        fprintf(worst, "%d %d\n", n, count);
    }
    fclose(best);
    fclose(worst);
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
