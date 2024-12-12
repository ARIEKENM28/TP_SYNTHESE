#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_prompt() {
    //Envoi des données au descripteur de fichier standard de sortie STDOUT_FILENO
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
