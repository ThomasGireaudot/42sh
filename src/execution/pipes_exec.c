/*
** EPITECH PROJECT, 2021
** pipes_exec.c
** File description:
** pipes_exec.c
*/

#include "my_sh.h"

int *int_arr_cpy(int *src, int *dest, int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
    return (dest);
}

int pipes_exec_switch(int *old, int *new, str_s *tmp)
{
    if (tmp->previous == NULL && tmp->next == NULL)
        return (cmd_execute(tmp->str, NULL, NULL));
    if (tmp->previous == NULL)
        return (cmd_execute(tmp->str, NULL, new));
    if (tmp->next == NULL)
        return (cmd_execute(tmp->str, old, NULL));
    return (cmd_execute(tmp->str, old, new));
}

int pipes_exec(char *cmd)
{
    str_s *list = split_str_to_list(cmd, "|");
    int *old = malloc(sizeof(int) * 2);
    int *new = malloc(sizeof(int) * 2);
    int ret;

    for (str_s *tmp = list; tmp != NULL; tmp = tmp->next) {
        if (tmp->previous != NULL)
            old = int_arr_cpy(new, old, 2);
        if (tmp->next != NULL)
            pipe(new);
        ret = pipes_exec_switch(old, new, tmp);
    }
    free(old);
    free(new);
    str_s_free_simple(list);
    waiting(_SHELL->head, _SHELL->pid);
    return (ret);
}