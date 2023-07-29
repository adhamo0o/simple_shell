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
#include <ctype.h>
#include <stdbool.h>

extern char **environ;

int main(int argc, char **argv);
void shell_loop(char *str);
char *read_line(void);
char **cut_line(char *line);
int num_builtins(void);
int exit_fun(char **args);
int cd_fun(char **args);
int env_fun(char **args);
void excution(char *dir, char **args);
int execute_ (char **args);
int lanch(char **args);
char **get_path();
void loop(void);
int setenv_fun(char **args);
int unsetenv_(char **args);
char *strcpy_(char *dest, char *src, int n);
char *strcat_(char *dest, char *src, int n);
char *strch_(char *s, char c);

#endif
