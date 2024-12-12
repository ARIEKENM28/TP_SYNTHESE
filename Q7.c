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

void execute_command_with_redirection(char *command, int *status, int *exec_time_ms) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();
    if (pid == 0) {
        
        char *argv[BUFFER_SIZE / 2 + 1];
        char *token = strtok(command, " ");
        int argc = 0;
        int fd_in = -1, fd_out = -1;

        while (token != NULL) {
            if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    fd_out = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd_out == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    //Gestion des redirections d'entrées sorties en utilisant dup2 pour reiriger STDOUT_FILENO
                    dup2(fd_out, STDOUT_FILENO);
                }
            } else if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    fd_in = open(token, O_RDONLY);
                    if (fd_in == -1) {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd_in, STDIN_FILENO);
                }
            } else {
                argv[argc++] = token;
            }
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;
         // Remplace le processus enfant par le programme contenu dans le argv
        execvp(argv[0], argv);
    
        perror("exec");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        
        waitpid(pid, status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        
        *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    } else {
        
        perror("fork");
    }
}
