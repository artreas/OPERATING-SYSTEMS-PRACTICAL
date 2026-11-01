#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child process\n");
        printf("My PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    else
    {
        printf("Parent process\n");
        printf("My PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
    }

    return 0;
}