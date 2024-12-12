#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "enseash.h"

void execute_command_with_pipe(char *command, int *status, int *exec_time_ms) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Split command by pipe
    char *cmd1 = strtok(command, "|");
    char *cmd2 = strtok(NULL, "|");

    if (cmd2 != NULL) {
        // Pipe handling
        int pipefd[2];
        pipe(pipefd);

        pid_t pid1 = fork();
        if (pid1 == 0) {
            // First child process
            close(pipefd[0]); // Close unused read end
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            char *argv1[BUFFER_SIZE / 2 + 1];
            char *token = strtok(cmd1, " ");
            int argc = 0;

            while (token != NULL) {
                argv1[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv1[argc] = NULL;

            execvp(argv1[0], argv1);
            // If exec fails
            perror("exec");
            exit(EXIT_FAILURE);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) {
            // Second child process
            close(pipefd[1]); // Close unused write end
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            char *argv2[BUFFER_SIZE / 2 + 1];
            char *token = strtok(cmd2, " ");
            int argc = 0;

            while (token != NULL) {
                argv2[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv2[argc] = NULL;

            execvp(argv2[0], argv2);
            // If exec fails
            perror("exec");
            exit(EXIT_FAILURE);
        }

        
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, status, 0);
        waitpid(pid2, status, 0);
    } else {

        pid_t pid = fork();
        if (pid == 0) {
            // Appel du processus enfant
            char *argv[BUFFER_SIZE / 2 + 1];
            char *token = strtok(command, " ");
            int argc = 0;

            while (token != NULL) {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv[argc] = NULL;
             // Remplace le processus enfant par la commande qui se trouve dans argv
            execvp(argv[0], argv);
            
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            
            waitpid(pid, status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);

            // Calcul du temps d'exécution en milliseconde
            *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
        } else {
            // échec du fork
            perror("fork");
        }
    }
}
