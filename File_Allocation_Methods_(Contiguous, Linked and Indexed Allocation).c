#include <stdio.h>

#define MAXBLOCKS 30

int disk[MAXBLOCKS];

void resetDisk()
{
    for (int i = 0; i < MAXBLOCKS; i++)
        disk[i] = 0;
}

void contiguousAllocation()
{
    int nf;
    resetDisk();

    printf("\n--- Contiguous Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);

    for (int f = 0; f < nf; f++)
    {
        int start, len, ok = 1;

        printf("File %d - starting block and length: ", f + 1);
        scanf("%d %d", &start, &len);

        for (int i = start; i < start + len; i++)
        {
            if (i < 0 || i >= MAXBLOCKS || disk[i] == 1)
            {
                ok = 0;
                break;
            }
        }

        if (!ok)
        {
            printf("Allocation failed.\n");
            continue;
        }

        for (int i = start; i < start + len; i++)
            disk[i] = 1;

        printf("File %d allocated blocks %d to %d\n",
               f + 1, start, start + len - 1);
    }
}

void linkedAllocation()
{
    int nf;
    resetDisk();

    printf("\n--- Linked Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);

    for (int f = 0; f < nf; f++)
    {
        int len, count = 0;
        int blocks[MAXBLOCKS];

        printf("File %d - number of blocks: ", f + 1);
        scanf("%d", &len);

        for (int i = 0; i < MAXBLOCKS && count < len; i++)
        {
            if (disk[i] == 0)
            {
                disk[i] = 1;
                blocks[count++] = i;
            }
        }

        printf("File %d allocated blocks: ", f + 1);

        for (int i = 0; i < count; i++)
        {
            printf("%d", blocks[i]);

            if (i < count - 1)
                printf(" -> ");
        }

        printf(" -> NULL\n");

        if (count < len)
            printf("Warning: Could not allocate all blocks.\n");
    }
}

void indexedAllocation()
{
    int nf;
    resetDisk();

    printf("\n--- Indexed Allocation ---\n");
    printf("Enter number of files: ");
    scanf("%d", &nf);

    for (int f = 0; f < nf; f++)
    {
        int len, indexBlock = -1, count = 0;
        int blocks[MAXBLOCKS];

        printf("File %d - number of data blocks: ", f + 1);
        scanf("%d", &len);

        for (int i = 0; i < MAXBLOCKS; i++)
        {
            if (disk[i] == 0)
            {
                indexBlock = i;
                disk[i] = 1;
                break;
            }
        }

        if (indexBlock == -1)
        {
            printf("No index block available.\n");
            continue;
        }

        for (int i = 0; i < MAXBLOCKS && count < len; i++)
        {
            if (disk[i] == 0)
            {
                disk[i] = 1;
                blocks[count++] = i;
            }
        }

        printf("File %d - Index block: %d\n", f + 1, indexBlock);
        printf("Data blocks: ");

        for (int i = 0; i < count; i++)
            printf("%d ", blocks[i]);

        printf("\n");

        if (count < len)
            printf("Warning: Could not allocate all data blocks.\n");
    }
}

int main()
{
    int choice;

    printf("Menu:\n");
    printf("1. Contiguous Allocation\n");
    printf("2. Linked Allocation\n");
    printf("3. Indexed Allocation\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        contiguousAllocation();
        break;

    case 2:
        linkedAllocation();
        break;

    case 3:
        indexedAllocation();
        break;

    default:
        printf("Invalid choice\n");
    }

    return 0;
}