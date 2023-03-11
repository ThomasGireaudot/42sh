/*
** EPITECH PROJECT, 2021
** cmd_execute.c
** File description:
** cmd_execute
*/

#include "my_sh.h"

char *take_first_arg(char *str)
{
    size_t size;
    char *ret;

    for (size = 0; str[size] != ' ' && str[size] != '\t' &&
        str[size] != '\0'; size++);
    ret = malloc(sizeof(char) * (size + 1));
    strncpy(ret, str, size);
    ret[size] = '\0';
    return (ret);
}

int first_arg_is(char *cmd, char *cmp)
{
    char *first_arg = take_first_arg(cmd);

    free(cmd);
    if (!strcmp(first_arg, cmp))
        return (1);
    return (0);
}

int cmd_execute(char *cmd, int *old, int *new)
{
    int ret;

    if (first_arg_is(strdup(cmd), "cd") == 1)
        return (my_chdir(_SHELL, cmd));
    if (first_arg_is(strdup(cmd), "unsetenv") == 1)
        return (my_unsetenv(split_str_to_strarr(cmd, " \t")));
    if (first_arg_is(strdup(cmd), "setenv") == 1) {
        ret = my_setenv(split_str_to_strarr(cmd, " \t"));
        if (ret != 2)
            return (ret);
    }
    if (first_arg_is(strdup(cmd), "echo") == 1)
        return (my_echo(cmd));
    return (forking(cmd, old, new));
}
