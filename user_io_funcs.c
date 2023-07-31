#include "simple_shell.h"

/**
 * **token_input - Function that gets user input and tokenizes it
 *
 * 
 * Return: Pointer to array of strings containing tokenized user input
 */

char **token_input(void)
{
	char **tokenized_string = NULL;
	char *user_input = NULL, *user_input_copy = NULL, *token;
	size_t bytes_read = 0;
	ssize_t nchars_read = 0;
	int num_tokens = 0, i;

	nchars_read = getline(&user_input, &bytes_read, stdin);
	/* Checking if the getline failed or user input is CTRL-D */
	if (nchars_read == -1)
	{
		free(user_input);
		return (NULL);
	}
	/* Allocating space for a copy of the user input */
	user_input_copy = malloc(sizeof(char) * (nchars_read + 1));
	if (user_input_copy == NULL)
		return (NULL);
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
	/* Allocating memory for array of strings to store parsed input */
	tokenized_string = malloc(sizeof(char *) * num_tokens);
	if (tokenized_string == NULL)
		return (NULL);
	token = strtok(user_input_copy, " ");
	/* Loop to malloc each index of tokenized_string, and copy each token */
	for (i = 0; token != NULL; i++)
	{
		tokenized_string[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(tokenized_string[i], token);
		token = strtok(NULL, " ");
	}
	tokenized_string[i] = NULL;
	free(user_input);
	free(user_input_copy);
	return (tokenized_string);
}
