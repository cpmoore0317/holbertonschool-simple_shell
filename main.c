#include "simple_shell.h"

/**
 * main - Simple Shell Program
 * @ac: Number of args passed to main
 * @argv: Args passed to main stored as strings
 * @env: Environ variable
 *
 * Return: 0 on Success, -1 on Failure
 */

int main(int ac, char **argv, char **env)
{
	char **tokenized_input = NULL;

	int i, interactive;

	(void)ac;
	(void)argv;
	(void)env;

	while (1)
	{
		interactive = isatty(STDIN_FILENO);
		if (interactive)
		{
			printf("%s", PROMPT);
		}

		tokenized_input = token_input();

		if (tokenized_input == NULL)
		{
			free(tokenized_input);
			printf("Exiting Shell...\n");
			return (-1);
		}

		cmd_exec(tokenized_input);

		for (i = 0; tokenized_input[i] != NULL; i++)
			free(tokenized_input[i]);
		free(tokenized_input);

		tokenized_input = NULL;
	}

	return (0);
}
