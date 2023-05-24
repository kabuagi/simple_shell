#include "shell.h"

/**
 * env_var - fuction to print the env varieble
 */

void env_var(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
