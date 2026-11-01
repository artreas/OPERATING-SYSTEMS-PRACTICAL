
#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int at[n], bt[n], rt[n], pr[n];
    int ct[n], tat[n], wt[n], pid[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("Enter Arrival Time, Burst Time and Priority for P%d: ",
               i + 1);

        if (scanf("%d %d %d", &at[i], &bt[i], &pr[i]) != 3 ||
            at[i] < 0 || bt[i] <= 0 || pr[i] < 0)
        {
            printf("Invalid input.\n");
            return 1;
        }

        rt[i] = bt[i];
    }

    printf("\nPriority Scheduling (Preemptive):\n");

    int time = 0;
    int completed = 0;

    while (completed < n)
    {
        int highest = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (highest == -1 || pr[i] < pr[highest])
                {
                    highest = i;
                }
            }
        }

        if (highest == -1)
        {
            time++;
            continue;
        }

        rt[highest]--;
        time++;

        if (rt[highest] == 0)
        {
            ct[highest] = time;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i],
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
