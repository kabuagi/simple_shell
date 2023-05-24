#include "shell.h"

/**
 * pid_fork - runs child process
 * @command:pointer to the string command
 */

void pid_fork(const char *command)
{
	pid_t pid;

	char *args[MAX_ARGUMENTS];

	char *token;

	int i = 0;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		token = strtok((char *)command, " ");
		while (token != NULL && i < MAX_ARGUMENTS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		execute_line(command, args);
		exit(EXIT_FAILURE);

	}
	else
	{
		wait(NULL);
	}
}
