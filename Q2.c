#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
