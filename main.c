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
	int i;

	(void)ac;
	(void)argv;
	(void)env;

	while (1) /* Creating a loop for the shell's prompt */
	{
		printf("%s", PROMPT);
		tokenized_input = token_input();
		/* Checking if the getline failed or user input is CTRL-D */
		if (tokenized_input == NULL)
		{
			printf("Exiting Shell...\n");
			return (-1);
		}
		/* Execute the command from the first argument cmd_exec(argv); */
		for (i = 0; tokenized_input[i] != NULL; i++)
			printf("tokenized_input[%d]: %s\n", i, tokenized_input[i]);

		for (i = 0; tokenized_input[i] != NULL; i++)
		{
			free(tokenized_input[i]);
		}
		free(tokenized_input[i]);
		free(tokenized_input);
	}
	free(tokenized_input);

	return (0);
}
