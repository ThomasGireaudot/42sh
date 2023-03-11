/*
** EPITECH PROJECT, 2021
** forking.c
** File description:
** forking
*/

#include "my_sh.h"

void duplicate_pipes(int *old, int *new)
{
    if (old != NULL) {
        dup2(old[0], STDIN_FILENO);
        close(old[0]);
        close(old[1]);
    }
    if (new != NULL) {
        dup2(new[1], STDOUT_FILENO);
        close(new[0]);
        close(new[1]);
    }
}

int forking(char *cmd, int *old, int *new)
{
    _SHELL->pid = fork();

    if (_SHELL->pid == 0) {
        duplicate_pipes(old, new);
        child(cmd);
    }
    if (old != NULL) {
        close(old[0]);
        close(old[1]);
    }
    return (0);
}
