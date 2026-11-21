#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    int status;

    printf("Parent process: PID = %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child process: PID = %d, Parent PID = %d\n",
               getpid(), getppid());

        printf("Child is about to exec 'ls -l'\n");

        execlp("ls", "ls", "-l", NULL);

        perror("exec failed");
        _exit(1);
    }
    else
    {
        printf("Parent waiting for child (PID = %d) to finish...\n", pid);
        wait(&status);
        if (WIFEXITED(status))
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        printf("Parent process resumes and exits.\n");
    }
    return 0;
}
