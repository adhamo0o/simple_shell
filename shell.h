#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buff */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for cmd chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: a string
 * @next: point to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function ptr struct
 *@arg: string generated from getline containing args
 *@argv: array of strings generated from arg
 *@path: string path for the current cmd
 *@argc: arg count
 *@line_count: error count
 *@err_num: error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@env_changed: on if environ was changed
 *@status: return status of the last exec'd cmd
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read line input
 *@histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* ptr to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contain a builtin string and related function
 *@type: builtin cmd flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/**
 * every file prototype collected under comment
 * with it's file name
*/

/* sh_loop.c */
int hshell_fun(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh_fun(char **);

/* errors.c */
void eputs_fun(char *);
int eputchar_fun(char);
int putfd_fun(char c, int fd);
int putsfd_fun(char *str, int fd);

/* string.c */
int strlen_fun(char *);
int strcmp_fun(char *, char *);
char *starts_with(const char *, const char *);
char *strcat_fun(char *, char *);

/* string1.c */
char *strcpy_fun(char *, char *);
char *strdup_fun(const char *);
void puts_fun(char *);
int putchar_fun(char);

/* exits.c */
char *strncpy_fun(char *, char *, int);
char *strncat_fun(char *, char *, int);
char *strchr_fun(char *, char);

/* tokenizer.c */
char **strtow_fun(char *, char *);
char **strtow2_fun(char *, char);

/* realloc.c */
char *memset_fun(char *, char, unsigned int);
void ffree_fun(char **);
void *realloc_fun(void *, unsigned int, unsigned int);

/* memory.c */
int bfree_fun(void **);

/* atoi.c */
int interactive_fun(info_t *);
int is_delim(char, char *);
int isalpha_fun(int);
int atoi_fun(char *);

/* errors1.c */
int erratoi_fun(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int myexit_fun(info_t *);
int mycd_fun(info_t *);
int myhelp_fun(info_t *);

/* builtin1.c */
int myhistory_fun(info_t *);
int myalias_fun(info_t *);

/*getline.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len):
ssize_t get_input(info_t *);
int getline_fun(info_t *, char **, size_t *);
void sigintHandler_fun(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *getenv_fun(info_t *, const char *);
int myenv_fun(info_t *);
int mysetenv_fun(info_t *);
int myunsetenv_fun(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int unsetenv_fun(info_t *, char *);
int setenv_fun(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
