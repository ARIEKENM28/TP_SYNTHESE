#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "enseash.h"

int main() {
    char buffer[BUFFER_SIZE];

    print_welcome_message();
    int last_status = 0;
    int exec_time_ms = 0;

    print_prompt();  // Afficher le prompt initial

    while (1) {
        ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read == 0) {
            break; // Gérer Ctrl+D (EOF)
        }

        buffer[bytes_read - 1] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (strncmp(buffer, EXIT_COMMAND, strlen(EXIT_COMMAND)) == 0) {
            break; // Gérer la commande exit
        }

        // Vérifier si la commande contient un pipe
        if (strstr(buffer, "|") != NULL) {
            execute_command_with_pipe(buffer, &last_status, &exec_time_ms);
        } else if (strstr(buffer, ">") != NULL || strstr(buffer, "<") != NULL) {
            execute_command_with_redirection(buffer, &last_status, &exec_time_ms);
        } else {
            execute_command_with_args(buffer, &last_status, &exec_time_ms);
        }

        // Afficher le prompt avec le statut et le temps d'exécution
        print_prompt_with_status(last_status, exec_time_ms);
    }

    print_exit_message();
    return 0;
}
