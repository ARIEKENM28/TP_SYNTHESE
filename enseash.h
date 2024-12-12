#ifndef ENSEASH_H
#define ENSEASH_H

#define BUFFER_SIZE 256
#define WELCOME_MESSAGE "Welcome to ENSEA Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "
#define EXIT_MESSAGE "Bye bye...\n"
#define EXIT_COMMAND "exit"
#define TIME_FORMAT_EXIT "enseash [exit:%d|%dms] %% "
#define TIME_FORMAT_SIGN "enseash [sign:%d|%dms] %% "

void print_welcome_message();
void print_exit_message();
void print_prompt();
void print_prompt_with_status(int status, int exec_time_ms);
void execute_command_with_args(char *command, int *status, int *exec_time_ms); // Question 6
void execute_command_with_redirection(char *command, int *status, int *exec_time_ms); // Question 7
void execute_command_with_pipe(char *command, int *status, int *exec_time_ms); // Question 8

#endif // ENSEASH_H
