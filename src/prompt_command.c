/*
** EPITECH PROJECT, 2021
** prompt_command.c
** File description:
** prompt_command.c
*/

#include "my_sh.h"

int str_is_empty(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return (1);
    return (0);
}

char *clean_input(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n')
            input[i] = '\0';
        if (input[i] == '&' && input[i + 1] == '&') {
            input[i] = 1;
            input[i + 1] = ' ';
        } else if (input[i] == '|' && input[i + 1] == '|') {
            input[i] = 2;
            input[i + 1] = ' ';
        }
        if (input[i] == '>' && input[i + 1] == '>') {
            input[i] = 3;
            input[i + 1] = ' ';
        } else if (input[i] == '<' && input[i + 1] == '<') {
            input[i] = 4;
            input[i + 1] = ' ';
        }
    }
    return (input);
}

char *prompt_command(int tty)
{
    char *input = NULL;
    char *dir = getcwd(NULL, 0);
    size_t size = 0;
    size_t eof = -1;

    if (dir == NULL)
        printf(tty ? "[42sh]# " : "");
    else
        printf(tty ? "[42sh@%s]# " : "", dir);
    free(dir);
    size = getline(&input, &size, stdin);
    if (size != eof)
        input = clean_input(input);
    else {
        free(input);
        printf(tty ? "exit\n" : "");
        return (NULL);
    }
    return (input);
}