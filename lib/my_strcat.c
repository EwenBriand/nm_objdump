/*
** EPITECH PROJECT, 2021
** Project Name
** File description:
** strcat
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int len;
    int i = 0;

    len = my_strlen(dest);
    for (i; i < my_strlen(src); ++i)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return (dest);
}
