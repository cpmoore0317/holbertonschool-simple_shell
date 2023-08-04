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

	printf("passed tokenized input to cmd_exec");

	if (tokenized_input)
	{
		printf("tokenized_input exists in cmd_exec\n");
		command = tokenized_input[0];

		if (strcmp(command, "exit") == 0)
		{
			free(tokenized_input);
			free(command);
			printf("free tokenized_input and command if command = exit");
			exit(EXIT_SUCCESS);
		}

		if (strcmp(command, "env") == 0)
		{
			printenv();
			return;
		}

		actual_command = get_location(command);

		if (access(actual_command, X_OK) != 0)
		{
			free(actual_command);
			printf("free actual_command after access failure");
			perror("Error: The file cannot be executed");
			return;
		}

		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
		}
		if (child_pid == 0)
		{
			if (execve(actual_command, tokenized_input, NULL) == -1)
			{
				/*free(actual_command);*/
				printf("Fail here?\n");
				perror("Error:");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(child_pid, &status, 0);
			/*free(actual_command);*/
			printf("actual_command free after waitpid");
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

	printf("Starting get location function\n");

	path = _getenv("PATH");

	if (path)
	{
		printf("path found\n");
		path_copy = strdup(path);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");

		if (stat(command, &buffer) == 0)
		{
			printf("is command already path?\n");
			return (command);
		}

		while (path_token != NULL)
		{
			printf("make it to while loop?\n");
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
		/*if (stat(command, &buffer) == 0)
		{
			printf("Fail here? (if command is already path)");
			return (command);
		}*/
		return (NULL);
	}
	return (NULL);
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
