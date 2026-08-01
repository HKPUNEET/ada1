#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dist[100][100], n, count;

/* Floyd-Warshall: O(n^3) shortest paths between all pairs */
void floyd()
{
    count = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                count++;
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
}

void tester()
{
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);
    count = 0;
    floyd();
    printf("Shortest Path Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }
    printf("Operations = %d\n", count);
}

void plotter()
{
    FILE *fp = fopen("floyd.txt", "w");
    srand(time(NULL));
    for (int sz = 2; sz <= 10; sz++)
    {
        n = sz;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = (i == j) ? 0 : rand() % 20 + 1;
        count = 0;
        floyd();
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
