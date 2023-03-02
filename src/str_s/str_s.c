/*
** EPITECH PROJECT, 2021
** str_s.c
** File description:
** str_s functions
*/

#include "my_sh.h"

int str_s_push(str_s *head, char *str)
{
    str_s *tmp = head;

    if (head == NULL || str == NULL)
        return (0);
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(str_s));
    if (tmp->next == NULL)
        return (0);
    tmp->next->str = strdup(str);
    if (tmp->next->str == NULL) {
        free(tmp->next);
        tmp->next = NULL;
        return (0);
    }
    tmp->next->previous = tmp;
    tmp->next->next = NULL;
    return (1);
}

str_s *split_str_to_list(char *arg, char *separators)
{
    str_s *head = malloc(sizeof(str_s));

    if (head == NULL)
        return (NULL);
    head->previous = NULL;
    head->next = NULL;
    head->str = strtok(arg, separators);
    for (int ret = 1; ret > 0;)
        ret = str_s_push(head, strtok(NULL, separators));
    return (head);
}

void str_s_free(str_s *head)
{
    if (head == NULL)
        return;
    if (head->next != NULL)
        str_s_free(head->next);
    free(head->str);
    free(head);
}

void str_s_free_simple(str_s *head)
{
    if (head == NULL)
        return;
    if (head->next != NULL)
        str_s_free_simple(head->next);
    free(head);
}

char **list_to_tab(str_s *env)
{
    char **tab = malloc(sizeof(char *) * (list_size(env) + 1));
    int i = 0;

    if (!tab)
        return (NULL);
    while (env->next != NULL) {
        tab[i] = strdup(env->str);
        if (!tab[i])
            return (NULL);
        i++;
        env = env->next;
    }
    tab[i] = NULL;
    return (tab);
}
