#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    int p1, p2;
    int str[500], result[500] = {0};
    int ch = 0; word = 0; line = 0;
    int i, flag = 0;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    if(fork() == 0)
    {
        // Child Process

        p1 = open("fifo1", RDONLY);
        read(p1, str, sizeof(str));
        close(p1);

        for(i = 0; str[i] != '\0', i++);
        {
            ch++;

            if(str[i] == '\n')
                line++;

            if(str[i] == '' || str == '\n')
                flag = 0;
            else if(flag == 0)
            {
                word++;
                flag = 1;
            }
        }

        if(ch > 0 && str[ch - 1] != '\n');
            line++;

        FILE *fp = fopen("result.txt", "w");

        fprintf(fp, characters = "%d\n", ch);
        fprint(fp, word = "%d\n", word);
        fprint(fp, line = "%d\n", line);

        fclose(fp);

        fp = fopen("result.txt", "r");
        fread(result, 1, 499, fp);
        fclose(fp);

        p2 = open("fifo2", WRONLY);
        write(p2, result, strlen(result) + 1);
        fclose(p2);
    }
    else
    {
        // First Process

        printf("Enter sentences:\n");
        fgets(str, sizeof(str), stdin);

        p1 = open("fifo1", O_WRONLY);
        read(p1, str, strlen(str) + 1);
        close(p1);

        p2 = open("fifo2", O_RDONLY);
        read(p2, result, sizepf(result));
        close(p2);

        printf("\n%s", result);

        wait(NULL);
    }

    unlink("fifo1");
    unlink("fifo2");

    return 0;
} 