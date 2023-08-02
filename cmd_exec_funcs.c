#include "simple_shell.h"

/**
 * cmd_exec - Function that executes command stored in tokenized input
 * @tokenized_input: Array of Strings containing user input
 *
 * Return: Always Void
 */

void cmd_exec(char **tokenized_input)
{
	char *command = NULL, *actual_command = NULL;
	pid_t child_pid;
	int status;

	if (tokenized_input)
	{
		command = tokenized_input[0];

		/*if (strcmp(command, "exit") == 0)
			run exit*/

		actual_command = get_location(command);

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
		}
		if (child_pid == 0)
		{
			if (execve(actual_command, tokenized_input, NULL) == -1)
			{
				free(actual_command);
				perror("Error:");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(child_pid, &status, 0);
			free(actual_command);
		}
	}
}

/**
 * *get_location - Function that takes in command and locates PATH location
 * @command: command to check against PATH
 *
 * Return: PATH of command passed as argument
 */

char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length = 0, directory_length = 0;
	struct stat buffer;

	path = _getenv("PATH");

	if (path)
	{
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}

/**
 * @name: key to find in envp
 *
 * Return: Pointer to the value matched with key
 */

char *_getenv(const char *name)
{
	extern char **environ;
	char **env;
	size_t name_len;

	name_len = strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (*env + name_len + 1);
		}
	}
	return (NULL);
}
