#include <stdio.h>
#include <stdlib.h>

/* Euclid: gcd via repeated remainder */
float euclid(int m, int n)
{
    int r;
    float count = 0;
    while (n)
    {
        count++;
        r = m % n;
        m = n;
        n = r;
    }
    printf("GCD = %d\n", m);
    return count;
}

/* Consecutive integer check from min down */
float consecutive(int m, int n)
{
    int t = (m < n) ? m : n;
    float count = 0;
    while (m % t || n % t)
    {
        count++;
        t--;
    }
    count++;
    printf("GCD = %d\n", t);
    return count;
}

/* Modified Euclid: uses subtraction */
float modified(int m, int n)
{
    float count = 0;
    while (n)
    {
        if (n > m)
        {
            int t = m;
            m = n;
            n = t;
        }
        m = m - n;
        count++;
    }
    printf("GCD = %d\n", m);
    return count;
}

void plotter(int algo)
{
    char fb[30], fw[30];
    if (algo == 1)
    {
        sprintf(fb, "euclid_best.txt");
        sprintf(fw, "euclid_worst.txt");
    }
    else if (algo == 2)
    {
        sprintf(fb, "consec_best.txt");
        sprintf(fw, "consec_worst.txt");
    }
    else
    {
        sprintf(fb, "modif_best.txt");
        sprintf(fw, "modif_worst.txt");
    }
    FILE *best = fopen(fb, "w"), *worst = fopen(fw, "w");
    for (int i = 10; i <= 100; i += 10)
    {
        float mn = 9999, mx = 0, c;
        for (int m = 2; m <= i; m++)
            for (int n = 2; n <= i; n++)
            {
                if (algo == 1)
                    c = euclid(m, n);
                else if (algo == 2)
                    c = consecutive(m, n);
                else
                    c = modified(m, n);
                if (c < mn)
                    mn = c;
                if (c > mx)
                    mx = c;
            }
        fprintf(best, "%.0f %.0f\n", (float)i, mn);
        fprintf(worst, "%.0f %.0f\n", (float)i, mx);
    }
    fclose(best);
    fclose(worst);
    printf("Data written.\n");
}

int main()
{
    int mode, algo, m, n;
    printf("1.Tester  2.Plotter\nMode: ");
    scanf("%d", &mode);
    printf("1.Euclid  2.Consecutive  3.Modified\nAlgo: ");
    scanf("%d", &algo);
    if (mode == 1)
    {
        printf("Enter m n: ");
        scanf("%d%d", &m, &n);
        float c = (algo == 1) ? euclid(m, n) : (algo == 2) ? consecutive(m, n)
                                                           : modified(m, n);
        printf("Basic Ops = %.0f\n", c);
    }
    else
        plotter(algo);
}
