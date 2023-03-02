/*
** EPITECH PROJECT, 2021
** sh.c
** File description:
** sh
*/

#include "my_sh.h"

str_s *env_to_struct(char **env)
{
    str_s *head = malloc(sizeof(str_s));

    if (head == NULL)
        return (head);
    head->str = strdup(env[0]);
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

void init_pos_struc(shell *sh)
{
    sh->pos = malloc(sizeof(position_t));
    sh->pos->act = NULL;
    sh->pos->prev = NULL;
    sh->pos->prev = malloc(sizeof(char) * 256);
    if (!sh->pos->prev)
        return;
    sh->pos->act = malloc(sizeof(char) * 256);
    if (!sh->pos->act)
        return;
    getcwd(sh->pos->act, 256);
    getcwd(sh->pos->prev, 256);
}

shell *setup_shell_struct(char **env)
{
    shell *sh = malloc(sizeof(shell));

    if (sh == NULL)
        return (NULL);
    if (env != NULL)
        sh->env = env_to_struct(env);
    else
        sh->env = NULL;
    init_pos_struc(sh);
    sh->head = NULL;
    return (sh);
}

void shell_free(shell *sh)
{
    str_s_free(sh->env);
    hist_l_free(sh->head);
    free(sh->pos);
}

int sh(char **env)
{
    char *input;
    shell *sh = setup_shell_struct(env);

    if (sh == NULL)
        return (FAILURE);
    while (1) {
        input = prompt_command(isatty(STDIN_FILENO));
        if (input == NULL)
            break;
        if (str_is_empty(input) == 1) {
            hist_l_add(sh->head, input);
            if (check_format(input)) {
                separators_exec(input, sh);
            }
        } else
            free(input);
    }
    shell_free(sh);
    return (SUCCESS);
}
