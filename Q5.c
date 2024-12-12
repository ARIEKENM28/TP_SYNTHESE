#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "enseash.h"

void execute_command_with_timing(char *command, int *status, int *exec_time_ms) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execlp(command, command, (char *)NULL);
        // If exec fails
        perror("exec");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate elapsed time in milliseconds
        *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    } else {
        // Fork failed
        perror("fork");
    }
}
