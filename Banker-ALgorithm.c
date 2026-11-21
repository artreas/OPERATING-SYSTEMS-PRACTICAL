
#include <stdio.h>

#define P 5
#define R 3

int available[R];
int maximum[P][R];
int allocation[P][R];
int need[P][R];

void calculateNeed()
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

int isSafe(int safeSeq[])
{
    int work[R];
    int finish[P] = {0};
    int count = 0;

    for (int j = 0; j < R; j++)
        work[j] = available[j];

    while (count < P)
    {
        int found = 0;

        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                int j;

                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            return 0;
    }

    return 1;
}

void printTable(int safeSeq[])
{
    int work[R];

    for (int j = 0; j < R; j++)
        work[j] = available[j];

    printf("\nInitial Available: ");
    for (int j = 0; j < R; j++)
        printf("%d ", work[j]);

    printf("\n\n");
    printf("Process   Allocation    Maximum     Available     Need\n");

    for (int i = 0; i < P; i++)
    {
        int p = safeSeq[i];

        printf("P%-8d", p);

        for (int j = 0; j < R; j++)
            printf("%d  ", allocation[p][j]);

        printf("     ");

        for (int j = 0; j < R; j++)
            printf("%d  ", maximum[p][j]);

        printf("     ");

        for (int j = 0; j < R; j++)
            work[j] += allocation[p][j];

        for (int j = 0; j < R; j++)
            printf("%d  ", work[j]);

        printf("     ");

        for (int j = 0; j < R; j++)
            printf("%d  ", need[p][j]);

        printf("\n");
    }

    printf("\nSafe Sequence: ");

    for (int i = 0; i < P; i++)
    {
        printf("P%d", safeSeq[i]);

        if (i < P - 1)
            printf(" -> ");
    }

    printf("\n");
}

int requestResources(int pid, int request[])
{
    if (pid < 0 || pid >= P)
    {
        printf("\nInvalid process number.\n");
        return 0;
    }

    for (int j = 0; j < R; j++)
    {
        if (request[j] < 0)
        {
            printf("\nInvalid request: negative resources are not allowed.\n");
            return 0;
        }

        if (request[j] > need[pid][j])
        {
            printf("\nError: Maximum claim exceeded.\n");
            return 0;
        }

        if (request[j] > available[j])
        {
            printf("\nRequest denied: Not enough resources available.\n");
            return 0;
        }
    }

    for (int j = 0; j < R; j++)
    {
        available[j] -= request[j];
        allocation[pid][j] += request[j];
        need[pid][j] -= request[j];
    }

    int safeSeq[P];

    if (isSafe(safeSeq))
    {
        printf("\nRequest can be granted safely.\n");
        printf("\nUpdated state after granting request:\n");
        printTable(safeSeq);
        return 1;
    }
    else
    {
        for (int j = 0; j < R; j++)
        {
            available[j] += request[j];
            allocation[pid][j] -= request[j];
            need[pid][j] += request[j];
        }

        printf("\nRequest denied: System would enter an unsafe state.\n");
        return 0;
    }
}

int main()
{
    printf("Enter available resources (%d values):\n", R);

    for (int j = 0; j < R; j++)
        scanf("%d", &available[j]);

    printf("\nEnter Maximum matrix (%d x %d):\n", P, R);

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &maximum[i][j]);

    printf("\nEnter Allocation matrix:\n");

    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    calculateNeed();

    int safeSeq[P];

    if (isSafe(safeSeq))
    {
        printf("\nSystem is in a SAFE state.\n");
        printTable(safeSeq);
    }
    else
    {
        printf("\nSystem is in an UNSAFE state.\n");
        return 0;
    }

    int pid;
    int request[R];

    printf("\nEnter process number requesting resources (0-4): ");
    scanf("%d", &pid);

    printf("\nEnter request vector (%d values): ", R);

    for (int j = 0; j < R; j++)
        scanf("%d", &request[j]);

    requestResources(pid, request);

    return 0;
}
