/*
** EPITECH PROJECT, 2021
** separators_exec.c
** File description:
** separators executions
*/

#include "my_sh.h"

int check_cmd_content(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\t')
            return (1);
    return (0);
}

void separators_exec_loop(int *sep_list, str_s *list)
{
    int result = 1;
    int sep_i = 0;

    if (check_cmd_content(list->str))
        result = pipes_exec(list->str);
    for (str_s *tmp = list->next; tmp != NULL && sep_list != NULL; tmp = tmp->next) {
        if (!check_cmd_content(tmp->str))
            continue;
        if (sep_list[sep_i] == 1 && result)
            result = pipes_exec(tmp->str);
        else if (sep_list[sep_i] == 2 && !result)
            result = pipes_exec(tmp->str);
        else
            result = 0;
        if (sep_list[sep_i] == ';')
            result = pipes_exec(tmp->str);
        sep_i++;
    }
}

void separators_exec(char *input)
{
    char separators[4] = {';', 1, 2, '\0'};
    int *sep_list = get_sep_list(input);
    str_s *list = split_str_to_list(input, separators);

    separators_exec_loop(sep_list, list);
    free(sep_list);
    str_s_free(list);
}
