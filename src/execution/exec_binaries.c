/*
** EPITECH PROJECT, 2021
** exec_binaries.c
** File description:
** Formating binaries and execute them
*/

#include "my_sh.h"

int list_size(str_s *env)
{
    str_s *current = env;
    int cpt = 0;

    while (current->next != NULL) {
        cpt++;
        current = current->next;
    }
    return (cpt);
}

char *path_create(char **path_split, char **command)
{
    char *bin = NULL;
    int bin_path_size;

    for (int i = 0; path_split[i]; i++) {
        bin_path_size = strlen(path_split[i]) + strlen("/") + strlen(command[0]);
        bin = malloc(sizeof(char) * (bin_path_size + 1));
        if (!bin)
            exit(84);
        strcpy(bin, path_split[i]);
        bin = strcat(bin, "/");
        bin = strcat(bin, command[0]);
        if (access(bin, F_OK) == 0)
            return (bin);
        free(bin);
    }
    return (bin);
}

char *search_path_var(char **env)
{
    for (int i = 0; env[i]; i++)
        if (strncmp(env[i], "PATH=", 5) == 0)
            return (strdup(&env[i][5]));
    return (NULL);
}

int relative_error(char *path, char *cmd)
{
    if (access(path, F_OK)) {
        write(2, cmd, strlen(cmd));
        write(2, ": Command not found.\n", 21);
        return (0);
    }
    if (access(path, X_OK)) {
        write(2, path, strlen(path));
        write(2, ": Permission denied.\n", 21);
        return (0);
    }
    return (1);
}

void exec_binaries(char **command)
{
    char **path_split = NULL;
    char **env = list_to_tab(_SHELL->env);
    char *cmd_path = NULL;

    if (strncmp(command[0], "/", 1) != 0 && strncmp(command[0], "./", 2) != 0 \
    && strncmp(command[0], "../", 3) != 0) {
        path_split = split_str_to_strarr(search_path_var(env), ":");
        if (path_split == NULL) {
            command_not_found(command, env);
        } else {
            cmd_path = path_create(path_split, command);
            if (relative_error(cmd_path, command[0]) == 0)
                exit(0);
        }
    } else if (relative_error(command[0], command[0]) == 0)
        exit(0);
    execve((!cmd_path ? command[0] : cmd_path), command, env);
}
