/*
** EPITECH PROJECT, 2021
** sh.c
** File description:
** sh
*/

#include "my_sh.h"

shell *_SHELL;

str_s *env_to_struct(char **env)
{
    str_s *head = malloc(sizeof(str_s));

    if (head == NULL)
        return (head);
    head->str = malloc(sizeof(char) * (strlen(env[0]) + 1));
    strcpy(head->str, env[0]);
    if (head->str == NULL) {
        free(head);
        return (NULL);
    }
    head->previous = NULL;
    head->next = NULL;
    for (int i = 1; env[i] != NULL; i++)
        str_s_push(head, env[i]);
    return (head);
}

void init_pos_struc(void)
{
    _SHELL->pos = malloc(sizeof(position_t));
    _SHELL->pos->act = NULL;
    _SHELL->pos->prev = malloc(sizeof(char) * 256);
    if (!_SHELL->pos->prev)
        exit(84);
    _SHELL->pos->act = malloc(sizeof(char) * 256);
    if (!_SHELL->pos->act)
        exit(84);
    getcwd(_SHELL->pos->act, 256);
    getcwd(_SHELL->pos->prev, 256);
}

void setup_shell_struct(char **env)
{
    _SHELL = malloc(sizeof(shell));

    if (_SHELL == NULL)
        return;
    if (env != NULL)
        _SHELL->env = env_to_struct(env);
    else
        _SHELL->env = NULL;
    init_pos_struc();
    _SHELL->head = NULL;
}

void shell_free(void)
{
    if (_SHELL->env)
        str_s_free(_SHELL->env);
    if (_SHELL->head)
        hist_l_free(_SHELL->head);
    if (_SHELL->pos) {
        free(_SHELL->pos->prev);
        free(_SHELL->pos->act);
        free(_SHELL->pos);
    }
    free(_SHELL);
}

int sh(char **env)
{
    char *input;
    setup_shell_struct(env);

    if (_SHELL == NULL)
        return (FAILURE);
    atexit(shell_free);
    while (1) {
        input = prompt_command(isatty(STDIN_FILENO));
        if (input == NULL || strcmp(input, "exit") == 0)
            break;
        if (str_is_empty(input) == 1) {
            hist_l_add(input);
            if (check_format(input))
                separators_exec(input);
        } else
            free(input);
    }
    if (input)
        free(input);
    return (SUCCESS);
}
