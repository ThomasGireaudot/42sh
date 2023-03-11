/*
** EPITECH PROJECT, 2021
** my_unsetenv.c
** File description:
** my_unsetenv
*/

#include "my_sh.h"

int my_arrlen(char **arr)
{
    int len;

    for (len = 0; arr[len] != NULL; len++);
    return (len - 1);
}

int my_unsetenv(char **cmd)
{
    char **parsed;

    if (my_arrlen(cmd) == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        free(cmd);
        return (1);
    }
    parsed = redirections_management_nodup(cmd);
    free(cmd);
    for (int i = 0; parsed[i] != NULL; i++) {
        str_s_pop_ncmp(_SHELL->env, parsed[i]);
    }
    for (int i = 0; parsed[i] != NULL; i++)
        free(parsed[i]);
    free(parsed);
    return (0);
}
