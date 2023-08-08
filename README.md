# Simple Shell Project in C

## Description
This simple shell, Better Bash (BBASH), is a command line interpreter developed in C language that emulates the some of the most basic functionality of `sh`.
## Man Page
The man page is a file which explains how Better Bash works in detail. To access the man page, use the following command:
```
$ man ./man_1_simple_shell
```
## Compilation
The following command accompanied by the specific flags are used to compile this program:
```
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
To run the shell, use the follwing command:
```
$ ./hsh
```
## Built-in Commands
Here is a list of the built-in commands, excluding the commands found in the PATH.
| Command |         Description           |
|:-------:|:-----------------------------:|
|  exit   | causes shell to terminate     |
|  env    | prints the current environemt |
## Usage
This shell can be used in interactive or non-interactive mode. The shell is typically used in the interactive mode. In order to enter interactive mode, the executable file is run in the command line. Here is an example:
```
$ ./hsh
BBASH$ ls
file1 file2 directory/
BBASH$ pwd
/home/user/holbertonschool-simple_shell/
BBASH$ echo hello_world
hello_world
BBASH$ exit
$
```
To use the non-interactive mode, pipe the command to the executable file. Here is an example:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c header.h

$ cat main.c
int main()
{
        return (0)
}
```
## Authors
* Chris Stephens [GitHub](https://github.com/Jtownokie)
* Parker Moore [GitHub](https://github.com/cpmoore0317)
