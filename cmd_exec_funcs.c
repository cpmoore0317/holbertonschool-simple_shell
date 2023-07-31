#include "simple_shell.h"

void cmd_exec(char **tokenized_input)
{
	char *command = NULL;

	if (tokenized_input)
	{
		command = tokenized_input[0];

		if (execve(command, tokenized_input, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
