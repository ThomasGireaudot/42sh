/*
** EPITECH PROJECT, 2021
** check_format.c
** File description:
** check_format.c
*/

#include "my_sh.h"

int check_format(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] == '<' || input[i] == 4 || input[i] == '>' ||
        input[i] == 3) && !check_redirections(input, i))
            return (0);
        if (input[i] == '|' && !check_pipe(input, i))
            return (0);
        if (input[i] == 1 && !check_and_separator(input, i))
            return (0);
        if (input[i] == 2 && !check_or_separator(input, i))
            return (0);
    }
    return (1);
}