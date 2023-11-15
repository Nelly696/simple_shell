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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
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
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shellloop.c */
int hsh(info_t *info, char **av);
int find_builtin_command(info_t *info);
void fork_exec_command(info_t *info);
void find_command_in_path(info_t *info);

/* parser.c */
int is_executable_cmd(info_t *shell_info, char *file_path);
char *duplicate_chars(char *path_string, int start_index, int stop_index);
char *find_cmd_in_path(info_t *shell_info, char *path_string, char *command);

/* loophsh.c */
int loophsh(char **);

/* exit.c */
void _errorPuts(char *str);
int _errorPutchar(char c);
int _putToFD(char c, int fd);
int _putsToFD(char *str, int fd);

/* get_string.c */
int _str_length(char *s);
int _str_compare(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_str_concat(char *dest, char *src);

/* get_string1.c */
char *custom_strcpy(char *destination, char *source);
char *custom_strdup(const char *str);
void custom_puts(char *str);
int custom_putchar(char c);

/* getline.c */
char *_uniqueStrncpy(char *dest, char *src, int n);
char *_uniqueStrncat(char *dest, char *src, int n);
char *_uniqueStrchr(char *s, char c);

/* tokenizer.c */
char **custom_strtow(char *input_str, char *delimiter_str);
char **custom_strtow2(char *input_str, char d);

/* realloc.c */
char *custom_memset(char *memory_area, char byte, unsigned int size);
void free_string_array(char **string_array);
void *cu_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size);

/* get_memory.c */
int free_and_null(void **pointer)

/* B_checks.c */
int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char *delim);
int is_alpha_character(int c);
int string_to_integer(char *s);

/* error.c */
int myErrAtoi(char *s);
void printError(info_t *info, char *estr);
int printDecimal(int input, int fd);
char *convertNumber(long int num, int base, int flags);
void removeComments(char *buf);

/* built_in.c */
int myExitShell(info_t *info);
int myChangeDirectory(info_t *info);
int myHelp(info_t *info);

/* builtin.c */
int myShellHistory(info_t *info);
int unsetAlias(info_t *info, char *str);
int setAlias(info_t *info, char *str);
int printAlias(list_t *node);
int myAlias(info_t *info);

/* get_line.c */
ssize_t _inputBuffer(info_t *info, char **buf, size_t *len);
ssize_t _getInput(info_t *info);
ssize_t _readBuffer(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* get_info.c */
void initialize_info(info_t *info);
void populate_info(info_t *info, char **av);
void deallocate_info(info_t *info, int all);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* get_env.c */
char **get_environment(info_t *info);
int unset_environment_var(info_t *info, char *var);
int set_environment_var(info_t *info, char *var, char *value);

/* get_history.c */
char *obtain_history_file(info_t *info);
int write_shell_history(info_t *info);
int read_history(info_t *info);
int append_to_history_list(info_t *info, char *buf, int history_entry_count);
int reenumerate_history(info_t *info);

/* get_lists.c */
list_t *add_new_node(list_t **list_head, const char *data, int index);
list_t *add_node_to_end(list_t **list_head, const char *data, int index);
size_t print_str_list(const list_t *head_node);
int delete_node_at_pos(list_t **list_head, unsigned int position);
void free_string_list(list_t **head_pointer);

/* get_lists1.c */
size_t get_list_length(const list_t *current_node);
char **convert_list_to_strings(list_t *head);
size_t display_list(const list_t *current_node);
list_t *find_node_starts_with(list_t *current_node, char *prefix, char c);
ssize_t obtain_node_index(list_t *head_node, list_t *target_node);

/* vars.c */
int is_command_chain(info_t *info, char *buffer, size_t *position);
void check_cmd_chain(info_t *info, char *b, size_t *p, size_t s, size_t l);
int substitute_aliases(info_t *info);
int substitute_variables(info_t *info);
int replace_string_content(char **old_content, char *new_content);

#endif
