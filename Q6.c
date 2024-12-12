#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enseash.h"

void execute_command_with_args(char *command, int *status, int *exec_time_ms) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();
    if (pid == 0) {
        // divise la chaine de caractères en tokens et les stocke dans le tableau argv
        char *argv[BUFFER_SIZE / 2 + 1];
        char *token = strtok(command, " ");
        int argc = 0;

        while (token != NULL) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        execvp(argv[0], argv);
        
        perror("exec");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
    
        waitpid(pid, status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // calcul du temps d'exécution en millisesonde
        *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    } else {
        
        perror("fork");
    }
}
