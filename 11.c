#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long count;

void heapify(int *a, int n, int i)
{
    int largest = i, l = 2*i+1, r = 2*i+2, t;
    count++;
    if (l < n && a[l] > a[largest]) largest = l;
    count++;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        t = a[i]; a[i] = a[largest]; a[largest] = t;
        heapify(a, n, largest);
    }
}

void buildHeap(int *a, int n)          // bottom-up
{
    for (int i = n/2-1; i >= 0; i--)
        heapify(a, n, i);
}

void heapSort(int *a, int n)
{
    buildHeap(a, n);
    for (int i = n-1; i > 0; i--) {
        int t = a[0]; a[0] = a[i]; a[i] = t;
        heapify(a, i, 0);
    }
}

void tester()
{
    int n, a[100];
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    count = 0;
    heapSort(a, n);
    printf("Sorted: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nComparisons = %ld\n", count);
}

void plotter()
{
    FILE *fb = fopen("heap_best.txt", "w");
    FILE *fw = fopen("heap_worst.txt", "w");
    srand(time(NULL));

    for (int n = 100; n <= 2000; n += 100) {
        int *a = malloc(n * sizeof(int));

        /* Best case – already a max-heap (descending) */
        for (int i = 0; i < n; i++) a[i] = n - i;
        count = 0;
        heapSort(a, n);
        fprintf(fb, "%d %ld\n", n, count);

        /* Worst case – ascending order */
        for (int i = 0; i < n; i++) a[i] = i;
        count = 0;
        heapSort(a, n);
        fprintf(fw, "%d %ld\n", n, count);

        free(a);
    }
    fclose(fb); fclose(fw);
    printf("Files written: heap_best.txt  heap_worst.txt\n");
}

int main()
{
    int ch;
    printf("1.Tester 2.Plotter\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1) tester();
    else plotter();
    return 0;
}
