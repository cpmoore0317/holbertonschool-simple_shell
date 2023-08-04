#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* Header Files */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Exit Status Macros */
/* EXIT_SUCCESS = 0 */
/* EXIT_FAILURE = -1 */
#define ERROR_MALLOC -77
#define EXIT_F_STAT -23
#define EXIT_F_ACCESS -24

/* Macros */
#define PROMPT "(BBASH)$ "
#define DELIM " \n\r\t"
/* Structures */

/* Prototypes */
void cmd_prep(char **tokenized_input);
char **token_input(void);
char *get_location(char *command);
void exec_fork(char *command, char **tokenized_input, int mallocd);
char *_getenv(const char *name);
void printenv(void);

#endif
