
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

    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n];
    int pid[n], completed[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        completed[i] = 0;

        printf("Enter Arrival Time, Burst Time and Priority for P%d: ",
               i + 1);

        if (scanf("%d %d %d", &at[i], &bt[i], &pr[i]) != 3 ||
            at[i] < 0 || bt[i] <= 0 || pr[i] < 0)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("\nPriority Scheduling (Non-Preemptive):\n");

    int time = 0;
    int count = 0;

    while (count < n)
    {
        int highest = -1;

        for (int i = 0; i < n; i++)
        {
            if (completed[i] == 0 && at[i] <= time)
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

        time += bt[highest];
        ct[highest] = time;

        tat[highest] = ct[highest] - at[highest];
        wt[highest] = tat[highest] - bt[highest];

        completed[highest] = 1;
        count++;
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
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
