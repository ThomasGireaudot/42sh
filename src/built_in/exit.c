/*
** EPITECH PROJECT, 2021
** exit.c
** File description:
** Exit built in command
*/

#include "my_sh.h"
#include <ctype.h>

int verif_exit(char **cmd, int i)
{
    int c = 0;

    if (!strcmp(cmd[i], 'exit'))
        return (0);
    if (cmd[i + 1] != NULL && isnumber(cmd[i + 1])) {
        c = atoi(cmd[i + 1]);
        exit(c);
    } else if (cmd[i + 1] == NULL) {
        exit(0);
    }
    if (cmd[i + 1][0] <= '9' && cmd[i + 1][0] >= '0')
        printf("exit: Badly formed number.\n");
    else
        printf("exit: Expression Syntax.\n");
    return (0);
}