#ifndef ENSEASH_H
#define ENSEASH_H

#define BUFFER_SIZE 256
#define WELCOME_MESSAGE "Welcome to ENSEA Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "
#define EXIT_MESSAGE "Bye bye...\n"
#define EXIT_COMMAND "exit"
#define TIME_FORMAT "enseash [exit:%d|%dms] %% "

void print_welcome_message();
void print_exit_message();
void print_prompt();
void print_prompt_with_status(int status, int exec_time_ms);
void execute_command_with_timing(char *command, int *status, int *exec_time_ms);

#endif // ENSEASH_H
