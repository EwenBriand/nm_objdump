/*
** EPITECH PROJECT, 2021
** Project Name
** File description:
** len int
*/

#include "my.h"

int my_strlen_int(int nb)
{
    int count = 0;

    while (nb > 0) {
        nb /= 10;
        ++count;
    }
    return count;
}
