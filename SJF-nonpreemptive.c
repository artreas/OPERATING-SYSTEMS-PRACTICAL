
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

    int at[n], bt[n], ct[n], tat[n], wt[n];
    int pid[n], completed[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        completed[i] = 0;

        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);

        if (scanf("%d %d", &at[i], &bt[i]) != 2 ||
            at[i] < 0 || bt[i] <= 0)
        {
            printf("Invalid arrival or burst time.\n");
            return 1;
        }
    }

    printf("\nSJF Non-Preemptive Scheduling:\n");

    int time = 0;
    int count = 0;

    while (count < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (completed[i] == 0 && at[i] <= time)
            {
                if (shortest == -1 ||
                    bt[i] < bt[shortest])
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        time += bt[shortest];
        ct[shortest] = time;

        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        completed[shortest] = 1;
        count++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i],
               tat[i], wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f ms",
           total_tat / n);

    printf("\nAverage Waiting Time    = %.2f ms\n",
           total_wt / n);

    return 0;
}
