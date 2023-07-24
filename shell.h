#ifndef SHELL_H
#define SHELL_H

<<<<<<< HEAD
#define buf_size 64
#define delim " \t\r\n\a"

=======
>>>>>>> 2af9a4c65843b0514f3cab5b751728b3de951003
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
<<<<<<< HEAD
=======
#include <stdbool.h>


void shell_loop(void);
char *read_line(void);
char **cut_line(char *line);
int execute_line(char **word);
int execute(char **args);
>>>>>>> 2af9a4c65843b0514f3cab5b751728b3de951003

#endif
