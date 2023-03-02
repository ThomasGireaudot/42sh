/*
** EPITECH PROJECT, 2021
** check_or_separator.c
** File description:
** check_or_separator.c
*/

#include "my_sh.h"

int check_or_invalid_null_after(char *input, int index)
{
    int tmp = index + 1;

    if (tmp == -1)
        return (0);
    while (tmp >= 0) {
        if (is_name(input[tmp]))
            break;
        else if (is_op(input[tmp]) || tmp == 0)
            return (0);
        tmp++;
    }
    return (1);
}

int check_or_invalid_null_before(char *input, int index)
{
    int tmp = index - 1;

    if (tmp == -1)
        return (0);
    while (tmp >= 0) {
        if (is_name(input[tmp]))
            break;
        else if (is_op(input[tmp]) || tmp == 0)
            return (0);
        tmp--;
    }
    return (1);
}

int check_or_separator(char *input, int index)
{
    int after = check_or_invalid_null_after(input, index);
    int before = check_or_invalid_null_before(input, index);

    if (!after) {
        write(2, "Invalid null command.\n", 22);
        return (0);
    }
    if (!before) {
        write(2, "Invalid null command.\n", 22);
        return (0);
    }
    return (1);
}