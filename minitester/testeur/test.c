#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int     status;
    int     count = 1;
    char    *line = NULL;
    size_t  linelen = 0;
    FILE    *test_file;

    if (argc == 2)
    {
        test_file = fopen(argv[1], "r");
        if (test_file)
        {
            while (getline(&line, &linelen, test_file) != -1)
            {
                printf("TEST NO %d:\n\n%s\n", count, line);
                pid_t process = fork();
                if (process == 0)
                    execl("/bin/bash", "bash", "--posix", "-c", line, (char *) NULL);
                else
                {
                    waitpid(process, &status, 0);
                    if (WIFEXITED(status))
                        printf("Exit status: %d\n", WEXITSTATUS(status));
                    else
                        printf("Child process did not exit normally\n");
                }
                printf("\n\n");
                free(line);
                line = NULL;
                linelen = 0;
                count++;
            }
            fclose(test_file);
        }
        return 0;
    }
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
}
