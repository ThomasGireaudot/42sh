/*
** EPITECH PROJECT, 2021
** status_management.c
** File description:
** status_management.c
*/

#include "my_sh.h"

int status_management(int status, hist_l unused *head)
{
    if (WIFEXITED(status) == 0) {
        if (WTERMSIG(status) == 8) {
            write(2, "Floating exception\n", 19);
            return (0);
        }
        if (WCOREDUMP(status) == 128) {
            write(2, "Segmentation fault (core dumped)\n", 33);
            return (0);
        }
    }
    return (0);
}

int waiting(hist_l *head, int pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    return (status_management(status, head));
}