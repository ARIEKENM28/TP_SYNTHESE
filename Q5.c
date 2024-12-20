#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "enseash.h"

void execute_command_with_timing(char *command, int *status, int *exec_time_ms) {
    // Déclaration des structures timespec pour stocker le temps de début et de fin et clock_gettime pour obtenir l'heure actuelle à l'aide de l'horloge monotone et le stocker dans le start
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork();
    if (pid == 0) {
        // Remplace le processus enfant par le nouveau programme exécuté par commande
        execlp(command, command, (char *)NULL);
        
        perror("exec");
        // Le processus enfant se termine en cas d'erreur
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        
        waitpid(pid, status, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        
        *exec_time_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    } else {
        
        perror("fork");
    }
}
