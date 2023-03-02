/*
** EPITECH PROJECT, 2021
** check_pipe.c
** File description:
** check_pipe.c
*/

#include "my_sh.h"

int check_pipe_invalid_null_after(char *input, int index)
{
    int tmp = index + 1;

    if (tmp == -1) {
        write(2, "Invalid null command.\n", 22);
        return (0);
    }
    while (tmp >= 0) {
        if (is_name(input[tmp])) {
            break;
        } else if (is_op(input[tmp]) || tmp == 0) {
            write(2, "Invalid null command.\n", 22);
            return (0);
        }
        tmp++;
    }
    return (1);
}

int check_pipe_invalid_null_before(char *input, int index)
{
    int tmp = index - 1;

    if (tmp == -1) {
        write(2, "Invalid null command.\n", 22);
        return (0);
    }
    while (tmp >= 0) {
        if (is_name(input[tmp])) {
            break;
        } else if (is_op(input[tmp]) || tmp == 0) {
            write(2, "Invalid null command.\n", 22);
            return (0);
        }
        tmp--;
    }
    return (1);
}

int check_pipe(char *input, int index)
{
    if (!check_pipe_invalid_null_after(input, index))
        return (0);
    if (!check_pipe_invalid_null_before(input, index))
        return (0);
    return (1);
}