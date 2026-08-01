#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* Selection sort: always O(n^2) comparisons regardless of input */
void selectionSort(int *a, int n)
{
    int i, j, minIdx, temp;
    count = 0;
    for (i = 0; i < n - 1; i++)
    {
        minIdx = i;
        for (j = i + 1; j < n; j++)
        {
            count++;
            if (a[j] < a[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
        {
            temp = a[minIdx];
            a[minIdx] = a[i];
            a[i] = temp;
        }
    }
}

void tester()
{
    int *arr, n, i;
    printf("Enter n: ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Before: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    selectionSort(arr, n);
    printf("\nAfter:  ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nComparisons = %d\n", count);
    free(arr);
}

void plotter()
{
    FILE *best = fopen("selbest.txt", "w"), *avg = fopen("selavg.txt", "w"), *worst = fopen("selworst.txt", "w");
    int *a, n, i;
    srand(time(NULL));
    for (n = 10; n <= 30000; n = (n < 10000) ? n * 10 : n + 10000)
    {
        a = malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = n - i;
        selectionSort(a, n);
        fprintf(worst, "%d %d\n", n, count);
        for (i = 0; i < n; i++)
            a[i] = i + 1;
        selectionSort(a, n);
        fprintf(best, "%d %d\n", n, count);
        for (i = 0; i < n; i++)
            a[i] = rand() % n;
        selectionSort(a, n);
        fprintf(avg, "%d %d\n", n, count);
        free(a);
    }
    fclose(best);
    fclose(avg);
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
