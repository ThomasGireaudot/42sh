/*
** EPITECH PROJECT, 2021
** child.c
** File description:
** child
*/

#include "my_sh.h"

void str_s_print(str_s *env)
{
    str_s *tmp;

    for (tmp = env; tmp != NULL; tmp = tmp->next)
        printf("%s\n", tmp->str);
}

void child(char *cmd)
{
    char **list = split_str_to_strarr(cmd, " \t");
    char **parsed = redirections_management(list);

    free(list);
    if (first_arg_is(strdup(cmd), "setenv") == 1 || first_arg_is(strdup(cmd), "env")) {
        str_s_print(_SHELL->env);
        for (int i = 0; parsed[i] != NULL; i++)
            free(parsed[i]);
        free(parsed);
        atexit(shell_free);
        exit(0);
    }
    exec_binaries(parsed);
    atexit(shell_free);
    exit(1);
}
