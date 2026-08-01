#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

/* Linear search: best O(1), worst O(n) */
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

void tester()
{
    int a[100], n, key;
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Enter key: ");
    scanf("%d", &key);
    int pos = linearSearch(a, n, key);
    if (pos == -1)
        printf("Not found\n");
    else
        printf("Found at index %d\n", pos);
    printf("Comparisons = %d\n", count);
}

void plotter()
{
    FILE *best = fopen("linbest.txt", "w"), *avg = fopen("linavg.txt", "w"), *worst = fopen("linworst.txt", "w");
    srand(time(NULL));
    for (int n = 2; n <= 1024; n *= 2)
    {
        int *a = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = 1;
        linearSearch(a, n, 1);
        fprintf(best, "%d %d\n", n, count); // best: first element
        for (int i = 0; i < n; i++)
            a[i] = rand() % n;
        linearSearch(a, n, rand() % n);
        fprintf(avg, "%d %d\n", n, count); // avg: random
        for (int i = 0; i < n; i++)
            a[i] = 0;
        linearSearch(a, n, 1);
        fprintf(worst, "%d %d\n", n, count); // worst: not present
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
