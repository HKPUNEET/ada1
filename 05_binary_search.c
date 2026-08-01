#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* Recursive binary search: O(log n) */
int binarySearch(int *a, int low, int high, int key)
{
    count++;
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (a[mid] == key)
        return mid;
    if (key < a[mid])
        return binarySearch(a, low, mid - 1, key);
    return binarySearch(a, mid + 1, high, key);
}

void tester()
{
    int a[100], n, key;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter sorted elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Enter key: ");
    scanf("%d", &key);
    count = 0;
    int pos = binarySearch(a, 0, n - 1, key);
    if (pos == -1)
        printf("Not found\n");
    else
        printf("Found at index %d\n", pos);
    printf("Comparisons = %d\n", count);
}

void plotter()
{
    FILE *best = fopen("binbest.txt", "w"), *avg = fopen("binavg.txt", "w"), *worst = fopen("binworst.txt", "w");
    srand(time(NULL));
    for (int n = 2; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = i;
        count = 0;
        binarySearch(a, 0, n - 1, a[(n - 1) / 2]);
        fprintf(best, "%d %d\n", n, count); // best: middle
        count = 0;
        binarySearch(a, 0, n - 1, rand() % n);
        fprintf(avg, "%d %d\n", n, count); // avg: random
        count = 0;
        binarySearch(a, 0, n - 1, -1);
        fprintf(worst, "%d %d\n", n, count); // worst: absent
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
    printf("1.Tester  2.Plotter\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1)
        tester();
    else
        plotter();
}
