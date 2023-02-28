/*
** EPITECH PROJECT, 2021
** my_put_nbr.c
** File description:
** print the number given
*/

#include "my.h"

void my_putnbr(int nb)
{
    int nb_r;

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb > 9) {
        nb_r = (nb % 10);
        nb = (nb / 10);
        my_putnbr(nb);
        my_putchar(nb_r + 48);
    } else {
        my_putchar(nb + 48);
    }
}
