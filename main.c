#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    while (1)
    {
        printf("myShell $ ");

        char input[256] = {0x0};
        char *ptr = input;
        char *args[64] = {NULL};

        fgets(input, 255, stdin);

        for (int i = 0; i < sizeof(args) && *ptr; ptr++)
        {
            if (*ptr == ' ')
                continue;
            if (*ptr == '\n')
                break;
            for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++)
                ;
            *ptr = '\0';
        }

        if (fork() == 0)
            exit(execvp(args[0], args));
        wait(NULL);
    }
}