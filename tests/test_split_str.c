/*
** EPITECH PROJECT, 2020
** tests_str_cpy.c
** File description:
** test str copies
*/

#include "my_test.h"

Test(char_cmp_str, char_cmp_str_test)
{
    char src[11] = "HelloWorld";

    cr_assert(char_cmp_str('a', src) == 0);
    cr_assert(char_cmp_str('e', src) == 1);
}
