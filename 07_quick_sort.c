#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* Hoare partition scheme */
int partition(int *a, int beg, int end)
{
    int pivot = a[beg], i = beg, j = end + 1;
    do
    {
        do
        {
            i++;
            count++;
        } while (i <= end && a[i] < pivot);
        do
        {
            j--;
            count++;
        } while (a[j] > pivot);
        swap(&a[i], &a[j]);
    } while (i < j);
    swap(&a[i], &a[j]);   // undo last swap
    swap(&a[beg], &a[j]); // pivot to final position
    return j;
}

void quickSort(int *a, int beg, int end)
{
    if (beg < end)
    {
        int split = partition(a, beg, end);
        quickSort(a, beg, split - 1);
        quickSort(a, split + 1, end);
    }
}

void tester()
{
    int n, *a;
    printf("Enter n: ");
    scanf("%d", &n);
    a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Before: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    count = 0;
    quickSort(a, 0, n - 1);
    printf("\nAfter:  ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\nComparisons = %d\n", count);
    free(a);
}

void plotter()
{
    FILE *fp = fopen("quickavg.txt", "w");
    FILE *fp1 = fopen("quickavgw.txt", "w");
    srand(time(NULL));
    for (int n = 4; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = rand() % n;
        count = 0;
        quickSort(a, 0, n - 1);
        fprintf(fp, "%d %d\n", n, count);
        free(a);
    }
    fclose(fp);
    printf("Data written to quickavg.txt\n");

for (int n = 4; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = i;
        count = 0;
        quickSort(a, 0, n - 1);
        fprintf(fp1, "%d %d\n", n, count);
        free(a);
    }
    fclose(fp1);
    printf("Data written to quickavgw.txt\n");
}


int main()
{
    int ch;
    printf("1.Tester  2.Plotter\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1)
        tester();
    else
        plotter();
}
