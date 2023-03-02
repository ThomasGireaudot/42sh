/*
** EPITECH PROJECT, 2021
** alias.c
** File description:
** alias
*/

#include "my_sh.h"

int check_char(char c, int *cpt_simple, int *cpt_double, int *first)
{
    if (c == 34) {
        *cpt_double += 1;
        if (*first == 0)
            *first = 2;
        return (0);
    } else if (c == 39) {
        if (*first == 0)
            *first = 1;
        *cpt_simple += 1;
        return (0);
    } else
        return (0);
}

int verif_style(char **cmd)
{
    int cpt_simple = 0;
    int cpt_double = 0;
    int first = 0;

    for (int i = 0; cmd[i] != NULL; i++)
        for (int j = 0; cmd[i][j] != '\0'; j++)
            check_char(cmd[i][j], &cpt_simple, &cpt_double, &first);
    if (cpt_simple % 2 != 0 && first == 1) {
        printf("Unmatched '''.\n");
        return (0);
    } else if (cpt_double % 2 != 0 && first == 2) {
        printf("Unmatched '%c'.\n", 34);
        return (0);
    }
    return (1);
}

void print_special_characters(char *cmd, char letter[8], char letter_c[8],
int i)
{
    for (int j = 0; letter[j]; j++) {
        if (letter[j] == cmd[i + 1])
            printf("%c", letter_c[j]);
    }
}

void e_option(char *arg_string, char letter[8], char letter_c[8])
{
    for (int i = 0; arg_string[i]; i++) {
        if (arg_string[i] == 92 && arg_string[i] != 34 && \
        arg_string[i] != 39) {
            print_special_characters(arg_string, letter, letter_c, i);
            i++;
        } else if (arg_string[i] != 34 && arg_string[i] != 39)
            printf("%c", arg_string[i]);
    }
}

int my_echo(char *cmd)
{
    char letter[8] = {'a', 'b', 't', 'n', 'v', 'f', 'r', '\0'};
    char letter_c[8] = {'\a', '\b', '\t', '\n', '\v', '\f', '\r', '\0'};
    char **cmd_split = split_str_to_strarr(cmd, " \t");

    if (verif_style(cmd_split) == 0)
        return (0);
    for (int i = (!strcmp(cmd_split[1], "-n") ? 2 : 1); cmd_split[i]; i++) {
        e_option(cmd_split[i], letter, letter_c);
        if (cmd_split[i + 1] != NULL)
            printf(" ");
    }
    if (strcmp(cmd_split[1], "-n"))
        printf("\n");
    return (0);
}