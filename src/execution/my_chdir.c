/*
** EPITECH PROJECT, 2021
** delivery [WSL: Ubuntu-20.04]
** File description:
** my_chdir
*/

#include "my_sh.h"

char **board(char *str)
{
    char **board = malloc(sizeof(char *) * 128);
    char *word = strtok(str, " \t\n");
    int j = 0;

    if (!board)
        return (NULL);
    for (; word != NULL; j++) {
        board[j] = word;
        word = strtok(NULL, " \t\n");
    }
    board[j] = NULL;
    return (board);
}

int position(shell *st)
{
    strcpy(st->pos->prev, st->pos->act);
    getcwd(st->pos->act, 256);
    return (0);
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
}

int execution(shell *st, char **tab_arg)
{
    if (tab_arg[1] != NULL && tab_arg[2] != NULL) {
        printf("cd: Too many argument.\n");
        return (0);
    }
    if (tab_arg[1] == NULL) {
        chdir("/home");
        return (0);
    }
    if (strcmp(tab_arg[1], "-") == 0 && tab_arg[2] == NULL) {
        chdir(st->pos->prev);
        return (0);
    }
    if (chdir(tab_arg[1]) == -1) {
        printf("%s: %s.\n", tab_arg[1], strerror(errno));
        return (0);
    }
    return (0);
}

int my_chdir(shell *st, char *command)
{
    char **tab_arg = NULL;

    if (position(st) == 84)
        return (84);
    tab_arg = board(command);
    if (tab_arg == NULL)
        return (84);
    execution(st, tab_arg);
    return (0);
}
