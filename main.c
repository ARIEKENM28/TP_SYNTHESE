#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "enseash.h"

int main() {
    char buffer[BUFFER_SIZE];

    print_welcome_message();
    int last_status = 0; // Initialiser avec le statut de succès
    int exec_time_ms = 0; // Initialiser le temps d'exécution à 0

    // Afficher le prompt initial
    print_prompt();

    while (1) {
        ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read == 0) {
            break; // Handle Ctrl+D (EOF)
        }

        buffer[bytes_read - 1] = '\0'; // Remove the newline character

        if (strncmp(buffer, EXIT_COMMAND, strlen(EXIT_COMMAND)) == 0) {
            break; // Handle exit command
        }

        // Execution of the command with timing
        execute_command_with_timing(buffer, &last_status, &exec_time_ms);

        // Afficher le prompt avec le statut après l'exécution d'une commande
        print_prompt_with_status(last_status, exec_time_ms);
    }

    print_exit_message();
    return 0;
}
