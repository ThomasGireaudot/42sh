/*
** EPITECH PROJECT, 2021
** my_setenv.c
** File description:
** my_setenv
*/

#include "my_sh.h"

int setenv_error(char **cmd_parsed)
{
    if (cmd_parsed == NULL) {
        write(2, "setenv: Allocation error.\n", 26);
        return (1);
    }
    return (0);
}

void set_var(char *to_push, char *name)
{
    str_s *tmp = _SHELL->env;

    for (; tmp != NULL; tmp = tmp->next)
        if (strncmp(name, tmp->str, strlen(name)) == 0) {
            free(tmp->str);
            tmp->str = strdup(to_push);
            return;
        }
    str_s_push(_SHELL->env, to_push);
}

int my_setenv_exec(char **cmd)
{
    char **cmd_parsed = redirections_management_nodup(cmd);
    char *name;
    char *to_push;

    if (setenv_error(cmd_parsed) == 1)
        return (0);
    name = strcat(cmd_parsed[1], "=");
    if (!cmd_parsed[2])
        set_var(name, cmd_parsed[1]);
    else {
        to_push = strcat(name, cmd_parsed[2]);
        set_var(to_push, cmd_parsed[1]);
        free(to_push);
    }
    free(name);
    for (int i = 0; cmd_parsed[i] != NULL; i++)
        free(cmd_parsed[i]);
    free(cmd_parsed);
    free(cmd);
    return (1);
}

int my_setenv(char **cmd)
{
    if (cmd == NULL) {
        write(2, "setenv: Allocation error.\n", 26);
        return (0);
    }
    if (count_alloc(cmd) < 2)
        return (2);
    if (count_alloc(cmd) > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        return (0);
    }
    return (my_setenv_exec(cmd));
}
