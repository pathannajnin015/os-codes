#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    char filename[100], data[500];

    pipe(p1);
    pipe(p2);

    if (fork() == 0)
    {
        // Child process
        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));

        FILE *fp = fopen(filename, "r");

        if (fp != NULL)
        {
            int n = fread(data, 1, sizeof(data) - 1, fp);
            data[n] = '\0';
            fclose(fp);

            write(p2[1], data, strlen(data) + 1);
        }
        else
        {
            strcpy(data, "File not found!");
            write(p2[1], data, strlen(data) + 1);
        }

        close(p1[0]);
        close(p2[1]);
    }
    else
    {
        // Parent process
        close(p1[0]);
        close(p2[1]);

        printf("Enter file name: ");
        scanf("%99s", filename);

        write(p1[1], filename, strlen(filename) + 1);

        read(p2[0], data, sizeof(data));

        printf("\nFile Contents:\n%s\n", data);

        close(p1[1]);
        close(p2[0]);

        wait(NULL);
    }

    return 0;
}
 