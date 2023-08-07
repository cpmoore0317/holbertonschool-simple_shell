#include "simple_shell.h"

/**
 * cmd_prep - Function that executes command stored in tokenized input
 * @tokenized_input: Array of Strings containing user input
 *
 * Return: Always Void
 */

void cmd_prep(char **tokenized_input)
{
	char *command = NULL, *actual_command = NULL;
	int mallocd = 0, not_mallocd = 0;

	command = tokenized_input[0];

	if (strcmp(command, "exit") == 0)
	{
		free(tokenized_input);
		free(command);
		exit(EXIT_SUCCESS);
	}

	if (strcmp(command, "env") == 0)
	{
		printenv();
		return;
	}

	actual_command = get_location(command);
	if (actual_command == NULL)
	{
		actual_command = command;
		not_mallocd = 1;
	}
	else if (actual_command && not_mallocd == 0)
		mallocd = 1;

	if (access(actual_command, X_OK) != 0)
	{
		if (mallocd == 1)
			free(actual_command);
		exit(EXIT_F_ACCESS);
	}

	exec_fork(actual_command, tokenized_input, mallocd);
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
		if (stat(command, &buffer) == 0)
		{
			free(path_copy);
			return (NULL);
		}
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
		perror("Error:");
		exit(EXIT_SUCCESS);
	}
	return (NULL);
}

/**
 * exec_fork - Function that forks and executes command
 * @command: file path of command to run
 * @tokenized_input: Tokenized input from stdin
 * @mallocd: Int variable to check if command needs to be freed
 *
 * Return: Always Void
 */

void exec_fork(char *command, char **tokenized_input, int mallocd)
{
	pid_t child_pid;
	extern char **environ;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
	}
	if (child_pid == 0)
	{
		if (execve(command, tokenized_input, environ) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (mallocd == 1)
			free(command);
	}
}

/**
 * *_getenv - Function that returns a pointer to a string in envp
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

/**
 * printenv - Prints the environment
 * Return: Always void
 */

void printenv(void)
{
	extern char **environ;
	char **env;

	for (env = environ; *env != NULL; env++)
		printf("%s\n", *env);
}
