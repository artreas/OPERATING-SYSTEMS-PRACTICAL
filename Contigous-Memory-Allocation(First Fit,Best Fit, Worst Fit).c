
#include <stdio.h>

#define MAX 20

void firstFit(int bsize[], int bn, int psize[], int pn)
{
    int block[MAX], allocation[MAX];

    for (int i = 0; i < bn; i++)
        block[i] = bsize[i];

    for (int i = 0; i < pn; i++)
        allocation[i] = -1;

    for (int i = 0; i < pn; i++)
    {
        for (int j = 0; j < bn; j++)
        {
            if (block[j] >= psize[i])
            {
                allocation[i] = j;
                block[j] -= psize[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");

    for (int i = 0; i < pn; i++)
    {
        printf("P%d\t%d\t", i + 1, psize[i]);

        if (allocation[i] == -1)
            printf("Not Allocated\n");
        else
            printf("B%d\n", allocation[i] + 1);
    }
}

void bestFit(int bsize[], int bn, int psize[], int pn)
{
    int block[MAX], allocation[MAX];

    for (int i = 0; i < bn; i++)
        block[i] = bsize[i];

    for (int i = 0; i < pn; i++)
        allocation[i] = -1;

    for (int i = 0; i < pn; i++)
    {
        int best = -1;

        for (int j = 0; j < bn; j++)
        {
            if (block[j] >= psize[i])
            {
                if (best == -1 || block[j] < block[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            allocation[i] = best;
            block[best] -= psize[i];
        }
    }

    printf("\n--- Best Fit ---\n");

    for (int i = 0; i < pn; i++)
    {
        printf("P%d\t%d\t", i + 1, psize[i]);

        if (allocation[i] == -1)
            printf("Not Allocated\n");
        else
            printf("B%d\n", allocation[i] + 1);
    }
}

void worstFit(int bsize[], int bn, int psize[], int pn)
{
    int block[MAX], allocation[MAX];

    for (int i = 0; i < bn; i++)
        block[i] = bsize[i];

    for (int i = 0; i < pn; i++)
        allocation[i] = -1;

    for (int i = 0; i < pn; i++)
    {
        int worst = -1;

        for (int j = 0; j < bn; j++)
        {
            if (block[j] >= psize[i])
            {
                if (worst == -1 || block[j] > block[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            allocation[i] = worst;
            block[worst] -= psize[i];
        }
    }

    printf("\n--- Worst Fit ---\n");

    for (int i = 0; i < pn; i++)
    {
        printf("P%d\t%d\t", i + 1, psize[i]);

        if (allocation[i] == -1)
            printf("Not Allocated\n");
        else
            printf("B%d\n", allocation[i] + 1);
    }
}

int main()
{
    int bn, pn;
    int bsize[MAX], psize[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &bn);

    printf("Enter block sizes: ");
    for (int i = 0; i < bn; i++)
        scanf("%d", &bsize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &pn);

    printf("Enter process sizes: ");
    for (int i = 0; i < pn; i++)
        scanf("%d", &psize[i]);

    if (bn <= 0 || bn > MAX || pn <= 0 || pn > MAX)
    {
        printf("Invalid input.\n");
        return 1;
    }

    firstFit(bsize, bn, psize, pn);
    bestFit(bsize, bn, psize, pn);
    worstFit(bsize, bn, psize, pn);

    return 0;
}
