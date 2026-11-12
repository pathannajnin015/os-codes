#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int p1, p2;
    char str[500], result[500] = {0};
    int ch = 0, word = 0, line = 0;
    int i, flag = 0, n;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    if(fork() == 0)
    {
        // Second Process

        p1 = open("fifo1", O_RDONLY);
        n = read(p1, str, 499);
        close(p1);

        if(n <= 0)
            exit(1);

        str[n] = '\0';

        for(i = 0; str[i] != '\0'; i++)
        {
            ch++;

            if(str[i] == '\n')
                line++;

            if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
                flag = 0;
            else if(flag == 0)
            {
                word++;
                flag = 1;
            }
        }

        if(ch > 0 && str[ch-1] != '\n')
            line++;

        FILE *fp = fopen("result.txt", "w");

        fprintf(fp, "Characters = %d\n", ch);
        fprintf(fp, "Words = %d\n", word);
        fprintf(fp, "Lines = %d\n", line);

        fclose(fp);

        fp = fopen("result.txt", "r");
        n = fread(result, 1, 499, fp);
        fclose(fp);
        result[n] = '\0';

        p2 = open("fifo2", O_WRONLY);
        write(p2, result, strlen(result) + 1);
        close(p2);

        exit(0);
    }
    else
    {
        // First Process

        printf("Enter sentences:\n");
        fgets(str, sizeof(str), stdin);

        p1 = open("fifo1", O_WRONLY);
        write(p1, str, strlen(str) + 1);
        close(p1);

        p2 = open("fifo2", O_RDONLY);
        n = read(p2, result, 499);
        close(p2);

        if(n > 0)
        {
            result[n] = '\0';
            printf("\n%s", result);
        }

        wait(NULL);
    }

    unlink("fifo1");
    unlink("fifo2");

    return 0;
}