#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include "enseash.h"

void print_prompt_with_status(int status, int exec_time_ms) {
    char prompt_with_status[BUFFER_SIZE];
    snprintf(prompt_with_status, BUFFER_SIZE, "enseash [exit:%d|%dms] %%", WEXITSTATUS(status), exec_time_ms);
    write(STDOUT_FILENO, prompt_with_status, strlen(prompt_with_status));
}
