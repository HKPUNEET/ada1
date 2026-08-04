#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* Linear Search */
int linearSearch(int *a, int n, int key)
{
    count = 0;
    for (int i = 0; i < n; i++)
    {
        count++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

/* Recursive Binary Search */
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

void tester(int algo)
{
    int a[100], n, key;
    printf("Enter n: ");
    scanf("%d", &n);

    if (algo == 2)
        printf("Enter sorted elements:\n");
    else
        printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter key: ");
    scanf("%d", &key);

    count = 0;
    int pos = (algo == 1) ? linearSearch(a, n, key)
                          : binarySearch(a, 0, n - 1, key);

    if (pos == -1)
        printf("Not found\n");
    else
        printf("Found at index %d\n", pos);
    printf("Comparisons = %d\n", count);
}

void plotter(int algo)
{
    FILE *best, *avg, *worst;

    if (algo == 1) {
        best  = fopen("linbest.txt", "w");
        avg   = fopen("linavg.txt", "w");
        worst = fopen("linworst.txt", "w");
    } else {
        best  = fopen("binbest.txt", "w");
        avg   = fopen("binavg.txt", "w");
        worst = fopen("binworst.txt", "w");
    }

    srand(time(NULL));

    for (int n = 2; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));

        if (algo == 1) {   // Linear Search
            // Best: key at first position
            for (int i = 0; i < n; i++) a[i] = 1;
            linearSearch(a, n, 1);
            fprintf(best, "%d %d\n", n, count);

            // Average: random
            for (int i = 0; i < n; i++) a[i] = rand() % n;
            linearSearch(a, n, rand() % n);
            fprintf(avg, "%d %d\n", n, count);

            // Worst: key not present
            for (int i = 0; i < n; i++) a[i] = 0;
            linearSearch(a, n, 1);
            fprintf(worst, "%d %d\n", n, count);
        }
        else {             // Binary Search
            for (int i = 0; i < n; i++) a[i] = i;

            // Best: middle element
            count = 0;
            binarySearch(a, 0, n - 1, a[(n - 1) / 2]);
            fprintf(best, "%d %d\n", n, count);

            // Average: random key
            count = 0;
            binarySearch(a, 0, n - 1, rand() % n);
            fprintf(avg, "%d %d\n", n, count);

            // Worst: key absent
            count = 0;
            binarySearch(a, 0, n - 1, -1);
            fprintf(worst, "%d %d\n", n, count);
        }
        free(a);
    }

    fclose(best);
    fclose(avg);
    fclose(worst);
    printf("Data written.\n");
}

int main()
{
    int mode, algo;
    printf("1.Tester  2.Plotter\nMode: ");
    scanf("%d", &mode);
    printf("1.Linear Search  2.Binary Search\nAlgo: ");
    scanf("%d", &algo);

    if (mode == 1)
        tester(algo);
    else
        plotter(algo);

    return 0;
}
