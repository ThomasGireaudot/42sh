/*
** EPITECH PROJECT, 2021
** check_redirections.c
** File description:
** check_redirections.c
*/

#include "my_sh.h"

int is_name(char c)
{
    if (c != 1 && c != 2 && c != 3 && c != 4 && c != '<' && c != '>'
    && c != '|' && c != ';' && c != ' ' && c != '\t' && c != '\0')
        return (1);
    return (0);
}

int is_op(char c)
{
    if (c == 1 || c == 2 || c == 3 || c == 4 || c == '<' || c == '>'
    || c == '|' || c == ';' || c == '\0')
        return (1);
    return (0);
}

int check_redir_mising_name(char *input, int index)
{
    size_t tmp = index + 1;

    while (tmp < strlen(input) + 1) {
        if (is_name(input[tmp])) {
            break;
        } else if (is_op(input[tmp])) {
            write(2, "Missing name for redirect.\n", 27);
            return (0);
        }
        tmp++;
    }
    return (1);
}

int check_redir_invalid_null(char *input, int index)
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

int check_redirections(char *input, int index)
{
    if (!check_redir_mising_name(input, index))
        return (0);
    if (!check_redir_invalid_null(input, index))
        return (0);
    return (1);
}
