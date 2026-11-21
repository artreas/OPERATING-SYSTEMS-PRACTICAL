#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int abs_diff(int a, int b)
{
    return a > b ? a - b : b - a;
}

void fcfs(int req[], int n, int head)
{
    int total = 0, cur = head;

    for (int i = 0; i < n; i++)
    {
        total += abs_diff(cur, req[i]);
        cur = req[i];
    }

    printf("FCFS Total Head Movement = %d\n", total);
}

void sstf(int req[], int n, int head)
{
    int visited[MAX] = {0};
    int total = 0, cur = head;

    for (int c = 0; c < n; c++)
    {
        int idx = -1, best = 999999;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && abs_diff(cur, req[i]) < best)
            {
                best = abs_diff(cur, req[i]);
                idx = i;
            }
        }

        visited[idx] = 1;
        total += best;
        cur = req[idx];
    }

    printf("SSTF Total Head Movement = %d\n", total);
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void scan(int req[], int n, int head, int diskSize)
{
    int arr[MAX + 2];

    for (int i = 0; i < n; i++)
        arr[i] = req[i];

    arr[n] = head;

    qsort(arr, n + 1, sizeof(int), cmp);

    int idx = 0;

    for (int i = 0; i <= n; i++)
        if (arr[i] == head)
        {
            idx = i;
            break;
        }

    int total = 0, cur = head;

    for (int i = idx + 1; i <= n; i++)
    {
        total += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    total += abs_diff(cur, diskSize - 1);
    cur = diskSize - 1;

    for (int i = idx - 1; i >= 0; i--)
    {
        total += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    printf("SCAN Total Head Movement = %d\n", total);
}

void cscan(int req[], int n, int head, int diskSize)
{
    int arr[MAX + 2];

    for (int i = 0; i < n; i++)
        arr[i] = req[i];

    arr[n] = head;

    qsort(arr, n + 1, sizeof(int), cmp);

    int idx = 0;

    for (int i = 0; i <= n; i++)
        if (arr[i] == head)
        {
            idx = i;
            break;
        }

    int total = 0, cur = head;

    for (int i = idx + 1; i <= n; i++)
    {
        total += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    total += abs_diff(cur, diskSize - 1);
    total += diskSize - 1;

    cur = 0;

    for (int i = 0; i < idx; i++)
    {
        total += abs_diff(cur, arr[i]);
        cur = arr[i];
    }

    printf("C-SCAN Total Head Movement = %d\n", total);
}

int main()
{
    int n, head, diskSize;
    int req[MAX];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, diskSize);
    cscan(req, n, head, diskSize);

    return 0;
}
