#include <stdio.h>
#include <stdlib.h>

int memo[50][50], wt[50], val[50];
int n, cap, count;

int max(int a, int b) { return a > b ? a : b; }

/* Top-down memoized recursion; -1 = not yet computed */
int knapsack(int i, int j)
{
    count++;
    if (memo[i][j] != -1)
        return memo[i][j];
    memo[i][j] = (j < wt[i]) ? knapsack(i - 1, j) : max(knapsack(i - 1, j), val[i] + knapsack(i - 1, j - wt[i]));
    return memo[i][j];
}

void initMemo()
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= cap; j++)
            memo[i][j] = (!i || !j) ? 0 : -1;
}

void tester()
{
    printf("Items n: ");
    scanf("%d", &n);
    printf("Capacity: ");
    scanf("%d", &cap);
    for (int i = 1; i <= n; i++)
    {
        printf("wt val [%d]: ", i);
        scanf("%d%d", &wt[i], &val[i]);
    }
    initMemo();
    count = 0;
    printf("Max Profit = %d\nOperations = %d\n", knapsack(n, cap), count);
}

void plotter()
{
    FILE *fp = fopen("knapsack_memo.txt", "a");
    for (n = 2; n <= 10; n++)
    {
        cap = 10;
        for (int i = 1; i <= n; i++)
        {
            wt[i] = rand() % 5 + 1;
            val[i] = rand() % 20 + 1;
        }
        initMemo();
        count = 0;
        knapsack(n, cap);
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
