/*
** EPITECH PROJECT, 2021
** Project Name
** File description:
** revstr
*/

#include "my.h"

char *my_revstr(char *str)
{
    int l_str = my_strlen(str);
    char cp[l_str];

    for (int i = 0; i < l_str; i++) {
        cp[i] = str[i];
    }
    for (int i = 0; i < l_str; i++) {
        str[i] = cp[l_str - 1 - i];
    }
    str[my_strlen(str)] = '\0';
    return str;
}
