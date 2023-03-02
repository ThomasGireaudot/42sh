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
    char *bin1 = NULL;
    char *bin2 = NULL;

    for (int i = 0; path_split[i]; i++) {
        bin1 = strdup(path_split[i]);
        bin2 = strcat(bin1, "/");
        free(bin1);
        bin1 = strcat(bin2, command[0]);
        free(bin2);
        if (access(bin1, F_OK) == 0)
            return (bin1);
        free(bin1);
    }
    return (bin1);
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

void exec_binaries(shell *sh, char **command)
{
    char **path_split = NULL;
    char **env = list_to_tab(sh->env);
    char *cmd_path = NULL;

    if (strncmp(command[0], "/", 1) != 0 && strncmp(command[0], "./", 2) != 0 \
    && strncmp(command[0], "../", 3) != 0) {
        path_split = split_str_to_strarr(search_path_var(env), ":");
        if (path_split == NULL) {
            command_not_found(command, sh, env);
        } else {
            cmd_path = path_create(path_split, command);
            if (relative_error(cmd_path, command[0]) == 0) {
                shell_free(sh);
                exit(0);
            }
        }
    } else if (relative_error(command[0], command[0]) == 0) {
        shell_free(sh);
        exit(0);
    }
    shell_free(sh);
    execve((!cmd_path ? command[0] : cmd_path), command, env);
}
