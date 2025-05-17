#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_COMMANDS 3

int main() {
    int pipes[NUM_COMMANDS - 1][2];  // Array to hold pipe file descriptors
    pid_t pids[NUM_COMMANDS];        // Array to hold process IDs

    // Step 1: Create pipes
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            return 1;
        }
    }

    // Step 2: Fork processes
    for (int i = 0; i < NUM_COMMANDS; i++) {
        pids[i] = fork();

        if (pids[i] == -1) {
            perror("fork");
            return 1;
        }

        if (pids[i] == 0) {
            // Child process
            if (i > 0) {
                // Duplicate the read end of the previous pipe to stdin
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][1]);  // Close the write end of the previous pipe
            }

            if (i < NUM_COMMANDS - 1) {
                // Duplicate the write end of the current pipe to stdout
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);  // Close the read end of the current pipe
            }

            // Close all other pipe file descriptors
            for (int j = 0; j < NUM_COMMANDS - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Execute the command
            char *cmd;
            switch (i) {
                case 0:
                    cmd = "ls";
                    execlp(cmd, cmd, NULL);
                    break;
                case 1:
                    cmd = "grep";
                    execlp(cmd, cmd, "txt", NULL);  // Example: grep for files with "txt" in the name
                    break;
                case 2:
                    cmd = "wc";
                    execlp(cmd, cmd, "-l", NULL);
                    break;
            }

            perror("execlp");
            exit(1);
        }
    }

    // Step 3: Close all pipe file descriptors in the parent
    for (int i = 0; i < NUM_COMMANDS - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Step 4: Wait for all child processes to complete
    for (int i = 0; i < NUM_COMMANDS; i++) {
        waitpid(pids[i], NULL, 0);
    }

    return 0;
}
