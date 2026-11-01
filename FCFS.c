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

    int at[n], bt[n], ct[n], tat[n], wt[n];
    int pid[n];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    printf("\n FCFS Scheduling:\n");
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {

                int t = at[j];
                at[j] = at[j + 1];
                at[j + 1] = t;

                t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;

                t = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {

            ct[i] = at[i] + bt[i];
        }
        else
        {
            if (at[i] > ct[i - 1])
            {

                ct[i] = at[i] + bt[i];
            }
            else
            {

                ct[i] = ct[i - 1] + bt[i];
            }
        }
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f ms", total_tat / n);
    printf("\nAverage Waiting Time    = %.2f ms\n", total_wt / n);

    return 0;
}