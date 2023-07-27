#include "simple_shell.h"

/**
 * main - Simple Shell Program
 *
 * Return: 0 on Success, -1 on Failure
 */

int main(int ac, char **argv, char **env)
{
	char *user_input = NULL, *user_input_copy = NULL, *token;
	size_t bytes_read = 0;
	ssize_t nchars_read = 0;
	int num_tokens = 0, i;

	(void)ac; (void)env;

	while (1) /* Creating a loop for the shell's prompt */
	{
		printf("%s", PROMPT);
		nchars_read = getline(&user_input, &bytes_read, stdin);
		/* Checking if the getline failed or user input is CTRL-D */
		if (nchars_read == -1)
		{
			printf("Exiting Shell...\n");
			return (-1);
		}
		/* Allocating space for a copy of the user input */
		user_input_copy = malloc(sizeof(char) * nchars_read);
		strcpy(user_input_copy, user_input);
		/* Split the string into an array of words */
		token = strtok(user_input, " ");
		/* Calculating number of tokens */
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, " ");
		}
		num_tokens++;
		/* Allocate space to hold array of words */
		argv = malloc(sizeof(char *) * num_tokens);
		/* Storing each token in the argv array */
		token = strtok(user_input_copy, " ");

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		/* Execute the command from the first argument */
		cmdexec(argv);
	}
	/* Free up allocated memory */
	free(user_input);
	free(user_input_copy);

	return (0);
}
