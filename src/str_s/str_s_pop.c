/*
** EPITECH PROJECT, 2021
** str_s_pop.c
** File description:
** str_s_pop
*/

#include "my_sh.h"

void str_s_pop_ncmp(str_s *list, char *str)
{
    str_s *tmp;
    str_s *to_free;

    if (list == NULL || str == NULL)
        return;
    if (strncmp(str, list->str, strlen(str)) == 0) {
        list = list->next;
        free(list->previous->str);
        free(list->previous);
    }
    for (tmp = list; tmp != NULL; tmp = tmp->next)
        if (strncmp(str, tmp->str, strlen(str)) == 0) {
            to_free = tmp;
            tmp = tmp->previous;
            if (to_free->next != NULL)
                to_free->next->previous = tmp;
            free(to_free->str);
            tmp->next = to_free->next;
            free(to_free);
        }
}
