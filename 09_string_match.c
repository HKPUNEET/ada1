#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int count = 0;

/* Brute-force string matching; returns index of match or -1 */
int stringMatch(char *text, char *pat, int n, int m)
{
    count = 0;
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m)
        {
            count++;
            if (pat[j] != text[i + j])
                break;
            j++;
        }
        if (j == m)
            return i; // found at index i
    }
    return -1;
}

void tester()
{
    char text[100], pat[100];
    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pat);
    int pos = stringMatch(text, pat, strlen(text), strlen(pat));
    printf(pos >= 0 ? "Found at %d\n" : "Not found\n", pos);
    printf("Comparisons = %d\n", count);
}

void plotter()
{
    FILE *best = fopen("strbest.txt", "w"), *worst = fopen("strworst.txt", "w"), *avg = fopen("stravg.txt", "w");
    char text[1001], pat[1001];
    int n = 1000;
    for (int i = 0; i < n; i++)
        text[i] = 'a';
    srand(time(NULL));
    for (int m = 10; m <= 1000; m = (m < 100) ? m + 10 : m + 100)
    {
        for (int i = 0; i < m; i++)
            pat[i] = 'a';
        stringMatch(text, pat, n, m);
        fprintf(best, "%d %d\n", m, count); // best: all match
        pat[m - 1] = 'b';
        stringMatch(text, pat, n, m);
        fprintf(worst, "%d %d\n", m, count); // worst: last char fails
        for (int i = 0; i < m; i++)
            pat[i] = 'a' + rand() % 3;
        stringMatch(text, pat, n, m);
        fprintf(avg, "%d %d\n", m, count); // avg: random
    }
    fclose(best);
    fclose(worst);
    fclose(avg);
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
