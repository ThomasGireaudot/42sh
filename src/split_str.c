/*
** EPITECH PROJECT, 2021
** split_str.c
** File description:
** split_str
*/

#include "my_sh.h"

int char_cmp_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (c == str[i])
            return (1);
    return (0);
}

int count_tokens(char *arg, char *separators)
{
    int result = 0;

    for (int i = 1; arg[i] != '\0'; i++)
        if (char_cmp_str(arg[i], separators) == 0 &&
            char_cmp_str(arg[i - 1], separators) == 1)
            result++;
    return (result);
}

char **split_str_to_strarr(char *arg, char *separators)
{
    char **str;
    int str_i = 0;

    if (arg == NULL || separators == NULL)
        return (NULL);
    str = malloc(sizeof(char *) * (count_tokens(arg, separators) + 3));
    if (str == NULL)
        return (NULL);
    str[str_i] = strtok(arg, separators);
    do {
        str_i++;
        str[str_i] = strtok(NULL, separators);
    } while (str[str_i] != NULL);
    return (str);
}