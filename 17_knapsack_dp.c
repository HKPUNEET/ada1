#include <stdio.h>
#include <stdlib.h>

int dp[50][50], wt[50], val[50];
int n, cap, count;

int max(int a, int b) { return a > b ? a : b; }

/* Classic 0/1 Knapsack bottom-up DP: O(n*cap) */
int knapsack()
{
    count = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= cap; j++)
        {
            if (!i || !j)
            {
                dp[i][j] = 0;
                continue;
            }
            count++;
            dp[i][j] = (j < wt[i]) ? dp[i - 1][j] : max(dp[i - 1][j], val[i] + dp[i - 1][j - wt[i]]);
        }
    return dp[n][cap];
}

void display()
{
    printf("DP Table:\n");
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= cap; j++)
            printf("%3d", dp[i][j]);
        printf("\n");
    }
    printf("Items selected: ");
    for (int i = n, j = cap; i > 0; i--)
        if (dp[i][j] != dp[i - 1][j])
        {
            printf("%d ", i);
            j -= wt[i];
        }
    printf("\nOperations = %d\n", count);
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
    printf("Max Profit = %d\n", knapsack());
    display();
}

void plotter()
{
    FILE *fp = fopen("knapsack_dp.txt", "a");
    for (n = 2; n <= 10; n++)
    {
        cap = 10;
        for (int i = 1; i <= n; i++)
        {
            wt[i] = rand() % 5 + 1;
            val[i] = rand() % 20 + 1;
        }
        count = 0;
        knapsack();
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
