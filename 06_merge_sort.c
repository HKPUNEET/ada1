#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long count = 0;

void merge(int *a, int low, int mid, int high)
{
    int temp[10000], i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high)
    {
        count++;
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= high)
        temp[k++] = a[j++];
    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];
}

/* Divide and conquer: O(n log n) always */
void mergeSort(int *a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

/* Builds a worst-case input by interleaving the two halves
   so that every merge performs the maximum number of comparisons */
void generateWorst(int *a, int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2;
    generateWorst(a, low, mid);
    generateWorst(a, mid + 1, high);

    // Interleave the two halves
    int temp[10000];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high)
    {
        temp[k++] = a[i++];
        if (j <= high)
            temp[k++] = a[j++];
    }
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];
}

void tester()
{
    int a[100], n;
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Before: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    count = 0;
    mergeSort(a, 0, n - 1);
    printf("\nAfter: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\nComparisons = %ld\n", count);
}

void plotter()
{
    FILE *fp = fopen("merge.dat", "w");
    srand(time(NULL));

    for (int n = 100; n <= 5000; n += 100)
    {
        int *a = malloc(n * sizeof(int));

        /* ---------- Average case : random array ---------- */
        for (int i = 0; i < n; i++)
            a[i] = rand() % 10000;
        count = 0;
        mergeSort(a, 0, n - 1);
        long avg = count;

        /* ---------- Worst case : interleaved array ---------- */
        for (int i = 0; i < n; i++)
            a[i] = i;                     // start with sorted 0..n-1
        generateWorst(a, 0, n - 1);       // rearrange into worst-case order
        count = 0;
        mergeSort(a, 0, n - 1);
        long worst = count;

        fprintf(fp, "%d %ld %ld\n", n, avg, worst);
        free(a);
    }
    fclose(fp);
    printf("Data written to merge.dat (n avg worst)\n");
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
