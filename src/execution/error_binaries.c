/*
** EPITECH PROJECT, 2021
** error_binaries.c
** File description:
** error_binaries
*/

#include "my_sh.h"

void command_not_found(char **command, char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        free(env[i]);
    free(env);
    write(2, command[0], strlen(command[0]));
    write(2, ": Command not found.\n", 20);
    exit(0);
}
