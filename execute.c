#include "shell.h"

/**
 * execute_cont - continues the execute fuction
 * @command:pointer to commands
 * @args:arguments to commands
 *
 */

void execute_cont(const char *command, char *const args[])
{
	if (access(command, X_OK) == 0)
	{
		execve(command, args, NULL);
		perror(command);
		return;
	}
}

/**
 * execute_line - executes the command
 * @command:pointer to the command string
 * @args:arguments to the commands
 *
 */

void execute_line(const char *command, char *const args[])
{
	char abs_path[MAX_COMMAND_LENGTH];

	char path_copy[MAX_PATH_LENGTH];

	char *path, *end, *path_token;

	execute_cont(command, args);
	path = getenv("PATH");
	if (path == NULL)
	{
		perror("path");
		return;
	}
	strncpy(path_copy, path, sizeof(path_copy) - 1);
	path_copy[sizeof(path_copy) - 1] = '\0';
	path_token = path_copy;
	while (*path_token != '\0')
	{
		end = strchr(path_token, ':');
		if (end == NULL)
		{
			end = path_token + strlen(path_token);
		}
		snprintf(abs_path, sizeof(abs_path), "%s/%s", path_token, command);
		if (access(abs_path, X_OK) == 0)
		{
			execve(abs_path, args, NULL);
			perror(abs_path);
			return;
		}
		if (*end == '\0')
		{
			break;
		}
		path_token = end + 1;
	}
	fprintf(stderr, "%s: not found\n", args[0]);
	exit(EXIT_FAILURE);
}


