/*
** EPITECH PROJECT, 2021
** redirections_management_nodup.c
** File description:
** redirections_management_nodup
*/

#include "my_sh.h"

void right_redir_nodup(char **list)
{
    int fd;
    char dbl_right[2] = {3, '\0'};

    if (strcmp(list[0], ">") == 0)
        fd = open(list[1], O_CREAT | O_WRONLY | O_TRUNC, 00777);
    if (strcmp(list[0], dbl_right) == 0)
        fd = open(list[1], O_CREAT | O_WRONLY | O_APPEND, 00777);
    if (fd == -1 && access(list[1], W_OK) == -1) {
        printf("%s: Permission denied.\n", list[1]);
        exit(84);
    } else if (fd == -1) {
        printf("Can't open '%s'.\n", list[1]);
        exit(84);
    }
    close(fd);
}

void left_redir_nodup(char **list)
{
    int fd;

    if (access(list[1], F_OK) == -1) {
        printf("%s: No such file or directory.\n", list[1]);
        exit(84);
    }
    if (access(list[1], R_OK) == -1) {
        printf("%s: Permission denied\n", list[1]);
        exit(84);
    }
    if (strcmp(list[0], "<") == 0)
        fd = open(list[1], O_RDONLY);
    close(fd);
}

char **redirections_management_nodup(char **list)
{
    char **parsed = malloc(sizeof(char *) * (count_alloc(list) + 2));
    int parsed_i = 0;
    char dbl_right[2] = {3, '\0'};
    char dbl_left[2] = {4, '\0'};

    if (parsed == NULL)
        return (NULL);
    for (int i = 0; list[i] != NULL; i++) {
        if (strcmp(list[i], ">") == 0 || strcmp(list[i], dbl_right) == 0) {
            right_redir_nodup(&list[i]);
            i++;
        } else if (strcmp(list[i], "<") == 0 || strcmp(list[i], dbl_left) == 0) {
            left_redir_nodup(&list[i]);
            i++;
        } else {
            parsed[parsed_i] = strdup(list[i]);
            parsed_i++;
        }
    }
    parsed[parsed_i] = NULL;
    return (parsed);
}
