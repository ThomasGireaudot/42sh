/*
** EPITECH PROJECT, 2021
** redirections_management.c
** File description:
** redirections_management
*/

#include "my_sh.h"

void right_redir(char **list)
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
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void redir_double_left(char *finisher)
{
    char *buffer;
    size_t size = 0;

    dup2(STDOUT_FILENO, STDOUT_FILENO);
    while (1) {
        printf("? ");
        size = getline(&buffer, &size, stdin);
        for (int i = 0; buffer[i] != '\0'; i++)
            if (buffer[i] == '\n')
                buffer[i] = '\0';
        if (strcmp(finisher, buffer) == 0)
            break;
        write(STDIN_FILENO, buffer, strlen(buffer));
        free(buffer);
    }
}

void left_redir(char **list)
{
    int fd;

    if (strcmp(list[0], "<") == 0) {
        if (access(list[1], F_OK) == -1) {
            printf("%s: No such file or directory.\n", list[1]);
            exit(84);
        }
        if (access(list[1], R_OK) == -1) {
            printf("%s: Permission denied\n", list[1]);
            exit(84);
        }
        fd = open(list[1], O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    } else
        redir_double_left(list[1]);
}

int count_alloc(char **list)
{
    int count = 0;
    char dbl_right[2] = {3, '\0'};
    char dbl_left[2] = {4, '\0'};

    if (list == NULL || list[0] == NULL)
        return (0);
    for (int i = 0; list[i] != NULL; i++) {
        if (strcmp(list[i], ">") == 0 || strcmp(list[i], dbl_right) == 0 ||
        strcmp(list[i], "<") == 0 || strcmp(list[i], dbl_left) == 0)
            i++;
        else
            count++;
    }
    return (count);
}

char **redirections_management(char **list)
{
    char **parsed = malloc(sizeof(char *) * (count_alloc(list) + 2));
    int parsed_i = 0;
    char dbl_right[2] = {3, '\0'};
    char dbl_left[2] = {4, '\0'};

    if (parsed == NULL)
        return (NULL);
    for (int i = 0; list[i] != NULL; i++) {
        if (strcmp(list[i], ">") == 0 || strcmp(list[i], dbl_right) == 0) {
            right_redir(&list[i]);
            i++;
        } else if (strcmp(list[i], "<") == 0 || \
        strcmp(list[i], dbl_left) == 0) {
            left_redir(&list[i]);
            i++;
        } else {
            parsed[parsed_i] = strdup(list[i]);
            parsed_i++;
        }
    }
    parsed[parsed_i] = NULL;
    return (parsed);
}
