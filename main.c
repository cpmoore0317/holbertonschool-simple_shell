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

	while (1)
	{
		printf("%s", PROMPT);
		nchars_read = getline(&user_input, &bytes_read, stdin);
		if (nchars_read == -1)
		{
			printf("Exiting Shell...\n");
			return (-1);
		}

		user_input_copy = malloc(sizeof(char) * nchars_read);
		strcpy(user_input_copy, user_input);

		token = strtok(user_input, " ");

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, " ");
		}
		num_tokens++;

		argv = malloc(sizeof(char *) * num_tokens);
		token = strtok(user_input_copy, " ");

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		free(user_input);
		free(user_input_copy);
	}
	return (0);
}
