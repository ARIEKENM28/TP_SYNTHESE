#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_welcome_message() {
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
}
