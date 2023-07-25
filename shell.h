#ifndef SHELL_H
#define SHELL_H


#define buf_size 64
#define delim " \t\r\n\a"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include <stdbool.h>


void shell_loop(char *str);
char *read_line(char *str);
char **cut_line(char *line, char *str);
int execute_line(char **word, char *str, int n);
char *get_executable_path(const char *executable_name);

#endif
