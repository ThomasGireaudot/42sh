/*
** EPITECH PROJECT, 2021
** hist_l.c
** File description:
** hist_l functions
*/

#include "my_sh.h"

void hist_l_add(hist_l *head, char *cmd)
{
    hist_l *cur;

    if (head == NULL) {
        head = malloc(sizeof(hist_l));
        head->previous = NULL;
        head->next = NULL;
        head->str = strdup(cmd);
    } else {
        cur = malloc(sizeof(hist_l));
        cur->previous = NULL;
        cur->next = head;
        cur->str = strdup(cmd);
        head->previous = cur;
        head = cur;
    }
}

void hist_l_free(hist_l *head)
{
    if (!head)
        return;
    if (head->next != NULL)
        hist_l_free(head->next);
    free(head->str);
    free(head);
}
