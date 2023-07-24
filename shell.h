#ifndef SHELL_H
#define SHELL_H

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


void shell_loop(void);
char *read_line(void);
char **cut_line(char *line);
int execute_line(char **word);
int execute(char **args);

#endif
