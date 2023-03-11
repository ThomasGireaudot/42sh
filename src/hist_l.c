/*
** EPITECH PROJECT, 2021
** hist_l.c
** File description:
** hist_l functions
*/

#include "my_sh.h"

void hist_l_add(char *cmd)
{
    hist_l *cur;
    hist_l *head = _SHELL->head;

    if (head == NULL) {
        head = malloc(sizeof(hist_l));
        head->previous = NULL;
        head->next = NULL;
        head->str = malloc(sizeof(cmd));
        strcpy(head->str, cmd);
    } else {
        cur = malloc(sizeof(hist_l));
        cur->previous = NULL;
        cur->next = head;
        cur->str = malloc(sizeof(cmd));
        strcpy(cur->str, cmd);
        head->previous = cur;
        head = cur;
    }
}

void hist_l_free(hist_l *head)
{
    for (hist_l *tmp = head; head; tmp = head) {
        head = head->next;
        free(tmp->str);
        free(tmp);
    }
}
