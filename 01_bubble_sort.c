#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count; // global comparison counter

/* Sorts array using bubble sort; returns comparison count */
int bubbleSort(int *a, int n)
{
    int i, j, temp, flag;
    count = 0;
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            count++;
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = 1;
            }
        }
        if (!flag)
            break; // already sorted - early exit
    }
    return count;
}

void tester()
{
    int *arr, n, i;
    printf("Enter n: ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Before: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    bubbleSort(arr, n);
    printf("\nAfter:  ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nComparisons = %d\n", count);
    free(arr);
}

void plotter()
{
    FILE *best = fopen("bubblebest.txt", "w");
    FILE *avg = fopen("bubbleavg.txt", "w");
    FILE *worst = fopen("bubbleworst.txt", "w");
    int *a, n, i;
    srand(time(NULL));
    for (n = 10; n <= 1000; n *= 10)
    {
        a = malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = n - i;
        bubbleSort(a, n);
        fprintf(worst, "%d %d\n", n, count); // worst: reverse
        for (i = 0; i < n; i++)
            a[i] = i + 1;
        bubbleSort(a, n);
        fprintf(best, "%d %d\n", n, count); // best: sorted
        for (i = 0; i < n; i++)
            a[i] = rand() % n;
        bubbleSort(a, n);
        fprintf(avg, "%d %d\n", n, count); // avg: random
        free(a);
    }
    fclose(best);
    fclose(avg);
    fclose(worst);
    printf("Data written. Run gnuplot to plot.\n");
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
