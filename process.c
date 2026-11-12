#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int a[10], n, i, j, temp;
    int pid;

    printf("Enter number of elements:");
    scanf("%d", &n);

    printf("Enter elements:");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    //FORK
    pid = fork();

    if(pid == 0)
    {
        print("\nChild Process");

        //SELECTION SORT
        for(i = 0; i< n;i++)
        {
            for(j = i+1; j < n; j++)
            {
                if(a[i] > a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }

        printf("Child Sorted Array");
        for(i = 0; i< n; i++)
            scanf("%d", &a[i])
    }
    else if(pid > 0)
    {
        wait(NULL);

        printf("\n\nParent Process\n");

        //BUBBLE SORT
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n-i-1; j++)
            {
                if(a[j] > a[j+1])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                }
            }
        }

        printf("Parent Sorted Array");
        for(i = 0; i < n; i++)
            scanf("%d", &a[i])
    }

    //ZOMBIE PROCESS
    printf("\n\nZombie Process");

    pid = fork();

    if(pid == 0)
    {
        printf("Child Finished\n");
        exit(0);
    }
    else
    {
        sleep(5);
        wait(NULL);
        printf("Zombie Removed\n");
    }

    //ORPHAN PROCESS
    printf("\nOrphan Process\n");

    pid = fork();

    if(pid = 0)
    {
        sleep(3);
        printf("Orphan child running\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Orphan Finished\n");
        exit(0);
    }
    return 0;
}




