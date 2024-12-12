#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_welcome_message() {
    //Envoi des données au descripteur de fichier standard STDOUT_FILENO
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}
