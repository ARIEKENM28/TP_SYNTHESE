#include <unistd.h>
#include <string.h>
#include "enseash.h"

//Affichage du message de sortie lorsque le shell enseash se termine 
void print_exit_message() {
    //Envoi des données au descripteur standard de sortie STDOUT_FILENO
    write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
}
