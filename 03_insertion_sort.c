#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* Insertion sort: best O(n), worst O(n^2) */
void insertionSort(int *a, int n)
{
    int i, j, key;
    count = 0;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            count++;
            a[j + 1] = a[j];
            j--;
        }
        if (j >= 0)
            count++; // one extra comparison that failed
        a[j + 1] = key;
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
    insertionSort(arr, n);
    printf("\nAfter:  ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nComparisons = %d\n", count);
    free(arr);
}

void plotter()
{
    FILE *best = fopen("insbest.txt", "w"), *avg = fopen("insavg.txt", "w"), *worst = fopen("insworst.txt", "w");
    int *a, n, i;
    srand(time(NULL));
    for (n = 10; n <= 30000; n = (n < 10000) ? n * 10 : n + 10000)
    {
        a = malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = n - i;
        insertionSort(a, n);
        fprintf(worst, "%d %d\n", n, count);
        for (i = 0; i < n; i++)
            a[i] = i + 1;
        insertionSort(a, n);
        fprintf(best, "%d %d\n", n, count);
        for (i = 0; i < n; i++)
            a[i] = rand() % n;
        insertionSort(a, n);
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
