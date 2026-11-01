
#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];
    int pid[n], inQueue[n];
    for (int i = 0; i < n; i++)
    {
        inQueue[i] = 0;
    }
    int queue[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);

        if (scanf("%d %d", &at[i], &bt[i]) != 2 ||
            at[i] < 0 || bt[i] <= 0)
        {
            printf("Invalid arrival or burst time.\n");
            return 1;
        }

        rt[i] = bt[i];
    }

    int tq;

    printf("Enter Time Quantum: ");
    if (scanf("%d", &tq) != 1 || tq <= 0)
    {
        printf("Invalid time quantum.\n");
        return 1;
    }

    printf("\nRound Robin Scheduling:\n");

    int front = 0, rear = 0, count = 0;
    int time = 0, completed = 0;

    time = at[0];

    for (int i = 1; i < n; i++)
    {
        if (at[i] < time)
            time = at[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (at[i] <= time)
        {
            queue[rear] = i;
            rear = (rear + 1) % n;
            count++;
            inQueue[i] = 1;
        }
    }

    while (completed < n)
    {
        if (count == 0)
        {
            int next = -1;

            for (int i = 0; i < n; i++)
            {
                if (rt[i] > 0 &&
                    (next == -1 || at[i] < at[next]))
                {
                    next = i;
                }
            }

            time = at[next];

            for (int i = 0; i < n; i++)
            {
                if (rt[i] > 0 && !inQueue[i] && at[i] <= time)
                {
                    queue[rear] = i;
                    rear = (rear + 1) % n;
                    count++;
                    inQueue[i] = 1;
                }
            }

            continue;
        }

        int p = queue[front];
        front = (front + 1) % n;
        count--;
        inQueue[p] = 0;

        int execute = (rt[p] < tq) ? rt[p] : tq;

        rt[p] -= execute;
        time += execute;

        for (int i = 0; i < n; i++)
        {
            if (i != p && rt[i] > 0 &&
                !inQueue[i] && at[i] <= time)
            {
                queue[rear] = i;
                rear = (rear + 1) % n;
                count++;
                inQueue[i] = 1;
            }
        }

        if (rt[p] == 0)
        {
            ct[p] = time;
            completed++;
        }
        else
        {
            queue[rear] = p;
            rear = (rear + 1) % n;
            count++;
            inQueue[p] = 1;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f ms",
           total_tat / n);

    printf("\nAverage Waiting Time    = %.2f ms\n",
           total_wt / n);

    return 0;
}
