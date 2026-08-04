#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* ================= Selection Sort ================= */
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

/* ================= Bubble Sort ================= */
void bubbleSort(int *a, int n)
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
            break;   // already sorted
    }
}

/* ================= Insertion Sort ================= */
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
            count++;          // the failing comparison
        a[j + 1] = key;
    }
}

/* ================= Tester ================= */
void tester(int algo)
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

    if (algo == 1) selectionSort(arr, n);
    else if (algo == 2) bubbleSort(arr, n);
    else insertionSort(arr, n);

    printf("\nAfter: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nComparisons = %d\n", count);

    free(arr);
}

/* ================= Plotter ================= */
void plotter(int algo)
{
    FILE *best, *avg, *worst;
    int *a, n, i;

    if (algo == 1) {
        best  = fopen("selbest.txt", "w");
        avg   = fopen("selavg.txt", "w");
        worst = fopen("selworst.txt", "w");
    }
    else if (algo == 2) {
        best  = fopen("bubblebest.txt", "w");
        avg   = fopen("bubbleavg.txt", "w");
        worst = fopen("bubbleworst.txt", "w");
    }
    else {
        best  = fopen("insbest.txt", "w");
        avg   = fopen("insavg.txt", "w");
        worst = fopen("insworst.txt", "w");
    }

    srand(time(NULL));

    // Different ranges for different algorithms
    int maxN = (algo == 2) ? 1000 : 30000;

    for (n = 10; n <= maxN; )
    {
        a = malloc(n * sizeof(int));

        // Worst case
        for (i = 0; i < n; i++) a[i] = n - i;
        if (algo == 1) selectionSort(a, n);
        else if (algo == 2) bubbleSort(a, n);
        else insertionSort(a, n);
        fprintf(worst, "%d %d\n", n, count);

        // Best case
        for (i = 0; i < n; i++) a[i] = i + 1;
        if (algo == 1) selectionSort(a, n);
        else if (algo == 2) bubbleSort(a, n);
        else insertionSort(a, n);
        fprintf(best, "%d %d\n", n, count);

        // Average case
        for (i = 0; i < n; i++) a[i] = rand() % n;
        if (algo == 1) selectionSort(a, n);
        else if (algo == 2) bubbleSort(a, n);
        else insertionSort(a, n);
        fprintf(avg, "%d %d\n", n, count);

        free(a);

        // Increment n
        if (algo == 2)
            n *= 10;                          // Bubble: 10,100,1000
        else
            n = (n < 10000) ? n * 10 : n + 10000;  // Selection & Insertion
    }

    fclose(best);
    fclose(avg);
    fclose(worst);
    printf("Data written.\n");
}

/* ================= Main ================= */
int main()
{
    int mode, algo;

    while (1)
    {
        printf("\n1.Tester  2.Plotter  0.Exit\nMode: ");
        scanf("%d", &mode);
        if (mode == 0) break;

        printf("1.Selection  2.Bubble  3.Insertion\nAlgo: ");
        scanf("%d", &algo);

        if (mode == 1)
            tester(algo);
        else
            plotter(algo);
    }
    return 0;
}
