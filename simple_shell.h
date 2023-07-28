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

/* Structures */

/* Prototypes */
void cmd_exec(char **argv);
#endif
