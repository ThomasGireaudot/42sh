/*
** EPITECH PROJECT, 2021
** cmd_execute.c
** File description:
** cmd_execute
*/

#include "my_sh.h"

int first_arg_is(char *cmd, char *cmp)
{
    char *first_arg = strtok(cmd, " \t");

    if (!strcmp(first_arg, cmp)) {
        free(cmd);
        return (1);
    }
    free(cmd);
    return (0);
}

int cmd_execute(char *cmd, int *old, int *new, shell *sh)
{
    int ret;

    if (first_arg_is(strdup(cmd), "cd") == 1)
        return (my_chdir(sh, cmd));
    if (first_arg_is(strdup(cmd), "unsetenv") == 1)
        return (my_unsetenv(split_str_to_strarr(cmd, " \t"), sh));
    if (first_arg_is(strdup(cmd), "setenv") == 1) {
        ret = my_setenv(split_str_to_strarr(cmd, " \t"), sh);
        if (ret != 2)
            return (ret);
    }
    if (first_arg_is(strdup(cmd), "echo") == 1)
        return (my_echo(cmd));
    return (forking(cmd, sh, old, new));
}
