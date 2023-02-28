/*
** EPITECH PROJECT, 2021
** my_putchar.c
** File description:
** write a charter
*/

#include <unistd.h>
#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
