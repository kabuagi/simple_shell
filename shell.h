#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define SHELL_PROMPT "shell$ "
#define MAX_ARGUMENTS 10
#define MAX_PATH_LENGTH 1024
extern char **environ;

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void execute_line(const char *command, char *const args[]);
void env_var(void);
void pid_fork(const char *command);
void run_shell(void);

#endif
