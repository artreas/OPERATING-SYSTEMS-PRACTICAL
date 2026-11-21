#include <stdio.h>

#define MAXFRAMES 10
#define MAXPAGES 50

int isPresent(int frames[], int nf, int page)
{
    for (int i = 0; i < nf; i++)
        if (frames[i] == page)
            return 1;

    return 0;
}

void fifo(int ref[], int n, int nf)
{
    int frames[MAXFRAMES];

    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int front = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, nf, ref[i]))
        {
            frames[front] = ref[i];
            front = (front + 1) % nf;
            faults++;
        }
    }

    printf("\nFIFO Page Faults = %d\n", faults);
}

void lru(int ref[], int n, int nf)
{
    int frames[MAXFRAMES], lastUsed[MAXFRAMES];

    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int filled = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        int pos = -1;

        for (int j = 0; j < nf; j++)
        {
            if (frames[j] == ref[i])
            {
                pos = j;
                break;
            }
        }

        if (pos == -1)
        {
            faults++;

            if (filled < nf)
            {
                frames[filled] = ref[i];
                lastUsed[filled] = i;
                filled++;
            }
            else
            {
                int lruIdx = 0;

                for (int j = 1; j < nf; j++)
                    if (lastUsed[j] < lastUsed[lruIdx])
                        lruIdx = j;

                frames[lruIdx] = ref[i];
                lastUsed[lruIdx] = i;
            }
        }
        else
        {
            lastUsed[pos] = i;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

void optimal(int ref[], int n, int nf)
{
    int frames[MAXFRAMES];

    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    int filled = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        if (isPresent(frames, filled, ref[i]))
            continue;

        faults++;

        if (filled < nf)
        {
            frames[filled++] = ref[i];
            continue;
        }

        int replaceIdx = -1, farthest = -1;

        for (int j = 0; j < nf; j++)
        {
            int k;

            for (k = i + 1; k < n; k++)
                if (frames[j] == ref[k])
                    break;

            if (k == n)
            {
                replaceIdx = j;
                break;
            }

            if (k > farthest)
            {
                farthest = k;
                replaceIdx = j;
            }
        }

        frames[replaceIdx] = ref[i];
    }

    printf("Optimal Page Faults = %d\n", faults);
}

int main()
{
    int ref[MAXPAGES], n, nf;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    if (n < 1 || n > MAXPAGES)
        return 0;

    printf("Enter reference string: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    if (nf < 1 || nf > MAXFRAMES)
        return 0;

    fifo(ref, n, nf);
    lru(ref, n, nf);
    optimal(ref, n, nf);

    return 0;
}