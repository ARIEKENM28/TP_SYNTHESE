#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

//Affichage du message de bienvenue dans le shell en utilisant la fonction Write
void display_welcome_message() {
    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 32);
    write(STDOUT_FILENO, "Pour quitter, tapez 'exit'.\n", 29);
}

void run_shell() {
    char command[256];// Stocke la comande saisie par l'utilisateur
    char prompt[] = "enseash> ";
    
    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        //Lecture de la commande saisie avec read
        if (read(STDIN_FILENO, command, sizeof(command)) == -1) {
            perror("Erreur de lecture");
            exit(-1);
        }
        
        // Retirer le caractère de nouvelle ligne
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            write(STDOUT_FILENO, "Au revoir!\n", 11);
            break;
        }

        // Créer un processus enfant
        pid_t pid = fork();

        if (pid == -1) {
            perror("Erreur de fork");
            exit(-1);
        }

        if (pid == 0) {
            // Processus enfant
            char *argv[] = {command, NULL};
            //exécution de la commande de l'utilisateur avec execvp
            if (execvp(command, argv) == -1) {
                perror("Erreur de commande");
            }
            exit(-1);
        } else {
            // Processus parent
            int status;
            waitpid(pid, &status, 0);
            char status_message[50];
            snprintf(status_message, sizeof(status_message), "Commande terminée avec le statut %d\n", WEXITSTATUS(status));
            write(STDOUT_FILENO, status_message, strlen(status_message));
        }
    }
}
