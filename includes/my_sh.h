/*
** EPITECH PROJECT, 2020
** binary.h
** File description:
** includes for binary binary
*/

#ifndef MY_SH
#define MY_SH

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#define unused __attribute__((unused))
#define SUCCESS 0
#define FAILURE 84

typedef struct hist_l {
    char *str;
    int ret;
    struct hist_l *next;
    struct hist_l *previous;
} hist_l;

typedef struct str_s {
    char *str;
    struct str_s *next;
    struct str_s *previous;
} str_s;

typedef struct position {
    char *act;
    char *prev;
} position_t;

typedef struct shell {
    hist_l *head;
    str_s *env;
    position_t *pos;
    int pid;
    char **alias;
} shell;

extern shell *_SHELL;

/* my_chdir */
int my_chdir(shell *st, char *command);
char **board(char *str);
int position(shell *st);
int execution(shell *st, char **tab_arg);
void free_tab(char **tab);

void hist_l_free(hist_l *head);
void hist_l_add(char *cmd);
str_s *split_str_to_list(char *arg, char *separators);
int str_s_push(str_s *head, char *str);
void str_s_free(str_s *head);
void str_s_free_simple(str_s *head);

int sh(char **env);
char *prompt_command(int tty);
int check_format(char *input);
int check_redirections(char *input, int index);
int check_pipe(char *input, int index);
int check_and_separator(char *input, int index);
int check_or_separator(char *input, int index);
int is_name(char c);
int is_op(char c);
void separators_exec(char *input);
int pipes_exec(char *cmd);
int cmd_execute(char *cmd, int *old, int *new);
int waiting(hist_l *head, int pid);
int *get_sep_list(char *input);
char **redirections_management(char **list);
int forking(char *cmd, int *old, int *new);
void child(char *cmd);
char **split_str_to_strarr(char *arg, char *separators);
void exec_binaries(char **command);
void shell_free(void);
char **list_to_tab(str_s *env);
int list_size(str_s *env);
int verif_exit(char **cmd, int i);
int count_alloc(char **list);
int my_setenv(char **cmd);
char **redirections_management_nodup(char **list);
int first_arg_is(char *cmd, char *cmp);
void str_s_pop_ncmp(str_s *list, char *str);
int my_unsetenv(char **cmd);
void command_not_found(char **command, char **env);
int str_is_empty(char *str);
int my_echo(char *cmd);
int char_cmp_str(char c, char *str);
void shell_free(void);

#endif
