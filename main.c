#include "simple_shell.h"

/**
 * main - Simple Shell Program
 *
 * Return: 0 on Success, -1 on Failure
 */

int main(int ac, char **argv, char **env)
{
	char *user_input, *token;
	size_t bytes_read = 0;
	ssize_t nchars_read = 0;

	(void)ac; (void)argv; (void)env;

	while (1)
	{
		printf("%s", PROMPT);
		nchars_read = getline(&user_input, &bytes_read, stdin);
		if (nchars_read == -1)
		{
			printf("Exiting Shell...");
			return (-1);
		}
		token = strtok(user_input, " ");
		argv = malloc(sizeof(c));


		free(user_input);
	}

	return (0);
}
