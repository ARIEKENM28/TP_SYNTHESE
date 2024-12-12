#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_exit_message() {
    write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
}
