#ifndef SHELL_H
#define SHELL_H


#define BUFSIZE 128
#define delimmeter " \t\r\n\a"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#include <stdbool.h>

extern char **environ;

void shell_loop(char *str);
char *read_line(void);
char **cut_line(char *line);
int execute_line(char **word, char *str, int n);
char *get_executable_path(const char *executable_name);

int num_builtins(void);
int execute(char **args);

int exit_fun(char **args);

int cd_fun(char **args);
void excution(char *dir, char **args);
int lanch(char **args);
char **get_path();
void loop(void);
int setenv_fun(char **args);
int unsetenv(char **args);

#endif
