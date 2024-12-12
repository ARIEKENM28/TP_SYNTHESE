#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include "enseash.h"

void print_prompt_with_status(int status, int exec_time_ms) {
    //Déclaration du tableau pour stocker le prompt formaté
    char prompt_with_status[BUFFER_SIZE];
    if (WIFEXITED(status)) {
        //Formatage du prompt
        snprintf(prompt_with_status, BUFFER_SIZE, TIME_FORMAT_EXIT, WEXITSTATUS(status), exec_time_ms);
    } 
    // on vérifie si le processus enfant s'est terminé à cause d'un signal
    else if (WIFSIGNALED(status)) {
        snprintf(prompt_with_status, BUFFER_SIZE, TIME_FORMAT_SIGN, WTERMSIG(status), exec_time_ms);
    }
    
    write(STDOUT_FILENO, prompt_with_status, strlen(prompt_with_status));
}
