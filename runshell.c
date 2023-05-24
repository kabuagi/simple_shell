#include "shell.h"

/**
 * shell_cont - continues with shell fuction
 * @command:pointer to command string
 * @args:arguments
 */

void shell_cont(const char *command, char *const args[])
{
	int exit_status;
	
	if (strcmp(command, "env") == 0)
	{
		env_var();
	}
	else if (strcmp(command, "exit") == 0 && args[1] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "exit") == 0 && args[1] != NULL)
	{
		exit_status = atoi(args[1]);
		exit(exit_status);
	}
	else if (strlen(command) == 0)
	{
		return;
	}
	else
	{
		pid_fork(command);
	}
}

/**
 * run_shell - run the shell
 *
 */

void run_shell(char *const args[])
{
	char *command = NULL;

	size_t len = 0;

	ssize_t bytes_read;

	while (1)
	{
		printf(SHELL_PROMPT);
		fflush(stdout);

		bytes_read = get_line(&command, &len, stdin);
		if (bytes_read == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if (bytes_read == 0)
		{
			printf("\n");
			break;
		}
		if (command[bytes_read - 1] == '\n')
		{
			command[bytes_read - 1] = '\0';
		}
		else
		{
		command[bytes_read] = '\0';
		}
		shell_cont(command, args);
		free(command);
		command = NULL;
	}
}

/**
 * main - calls the shell fuction
 *
 * Return: 0 on success
 */

int main(void)
{
	char *args[] = {"shell",NULL};

	run_shell(args);
	return (0);
}
