/*
** EPITECH PROJECT, 2021
** separators.c
** File description:
** separators.c
*/

#include "my_sh.h"

int get_list_size(char *input)
{
    int mode = 0;
    int size = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (mode == 0 && (input[i] == ';' || input[i] == 1 || input[i] == 2)) {
            mode = 1;
            size++;
        }
        if (mode == 1 && input[i] != ' ' && input[i] != '\t' && input[i] != ';'
        && input[i] != 1 && input[i] != 2)
            mode = 0;
    }
    return (size);
}

int *put_sep_in_list(char *input, int *sep_list)
{
    int mode = 0;
    int list_i = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (mode == 0 && (input[i] == ';' || input[i] == 1 || input[i] == 2)) {
            mode = 1;
            sep_list[list_i] = input[i];
            list_i++;
        }
        if (mode == 1 && input[i] != ' ' && input[i] != '\t' && input[i] != ';'
        && input[i] != 1 && input[i] != 2)
            mode = 0;
    }
    return (sep_list);
}

int *get_sep_list(char *input)
{
    int size = get_list_size(input);
    int *sep_list;

    sep_list = malloc(sizeof(int) * (size + 1));
    if (sep_list == NULL)
        return (NULL);
    sep_list = put_sep_in_list(input, sep_list);
    return (sep_list);
}