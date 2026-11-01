#include <stdio.h>

struct Process
{
    int pid, at, bt, pr;
    int rem, ct, tat, wt;
};

void reset(struct Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].rem = p[i].bt;
        p[i].ct = 0;
    }
}

void input(struct Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
    }
}

void display(struct Process p[], int n)
{
    float avgTAT = 0, avgWT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgTAT += p[i].tat;
        avgWT += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT = %.2f\n", avgWT / n);
}

int better(struct Process a, struct Process b, int mode)
{
    if (mode == 0)
        return a.at < b.at;
    if (mode == 1)
        return a.rem < b.rem;
    if (mode == 2)
        return a.pr < b.pr;
    return a.rem > b.rem;
}

void schedule(struct Process p[], int n, int mode, int preemptive)
{
    int time = 0, completed = 0;

    reset(p, n);

    while (completed < n)
    {
        int idx = -1;

        for (int i = 0; i < n; i++)
            if (p[i].rem > 0 && p[i].at <= time)
                if (idx == -1 || better(p[i], p[idx], mode))
                    idx = i;

        if (idx == -1)
        {
            time++;
            continue;
        }

        int run = preemptive ? 1 : p[idx].rem;

        time += run;
        p[idx].rem -= run;

        if (p[idx].rem == 0)
        {
            p[idx].ct = time;
            completed++;
        }
    }

    display(p, n);
}

void roundRobin(struct Process p[], int n, int tq)
{
    int queue[n];
    int visited[n];
    int front = 0, size = 0;
    int time = 0, completed = 0;

    reset(p, n);

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    while (completed < n)
    {

        for (int i = 0; i < n; i++)
            if (!visited[i] && p[i].at <= time)
            {
                queue[(front + size) % n] = i;
                size++;
                visited[i] = 1;
            }

        if (size == 0)
        {
            time++;
            continue;
        }

        int idx = queue[front];
        front = (front + 1) % n;
        size--;

        int run = (p[idx].rem < tq) ? p[idx].rem : tq;

        time += run;
        p[idx].rem -= run;

        for (int i = 0; i < n; i++)
            if (!visited[i] && p[i].at <= time)
            {
                queue[(front + size) % n] = i;
                size++;
                visited[i] = 1;
            }

        if (p[idx].rem > 0)
        {
            queue[(front + size) % n] = idx;
            size++;
        }
        else
        {
            p[idx].ct = time;
            completed++;
        }
    }

    display(p, n);
}

int main()
{
    int n, choice, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    input(p, n);

    while (1)
    {
        printf("\n\n===== CPU SCHEDULING =====\n");
        printf("1. FCFS\n");
        printf("2. SJF Non-Preemptive\n");
        printf("3. SJF Preemptive\n");
        printf("4. Priority Non-Preemptive\n");
        printf("5. Priority Preemptive\n");
        printf("6. LJF Non-Preemptive\n");
        printf("7. LJF Preemptive\n");
        printf("8. Round Robin\n");
        printf("9. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            schedule(p, n, 0, 0);
            break;
        case 2:
            schedule(p, n, 1, 0);
            break;
        case 3:
            schedule(p, n, 1, 1);
            break;
        case 4:
            schedule(p, n, 2, 0);
            break;
        case 5:
            schedule(p, n, 2, 1);
            break;
        case 6:
            schedule(p, n, 3, 0);
            break;
        case 7:
            schedule(p, n, 3, 1);
            break;

        case 8:
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);

            if (tq <= 0)
            {
                printf("Invalid time quantum.\n");
                break;
            }

            roundRobin(p, n, tq);
            break;

        case 9:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}