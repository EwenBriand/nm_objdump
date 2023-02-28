/*
** EPITECH PROJECT, 2022
** stumper
** File description:
** make_word_array
*/

#include <stdlib.h>
#include "my.h"

static int count_nb_words(char *str)
{
    int nb_words = 1;

    for (int i = 0; str[i] != '\0'; ++i)
        if (str[i] == '\n')
            ++nb_words;

    return nb_words;
}

static char **malloc_word_array(char *str, int nb_words)
{
    char **array = malloc(sizeof(char *) * (nb_words + 1));

    if (array == NULL)
        return NULL;

    return array;
}

char **make_word_array(char *array)
{
    int count = count_nb_words(array);
    char **word_array = malloc_word_array(array, count);
    int pos = 0;
    int j = 0;

    if (word_array == NULL)
        return NULL;
    for (int i = 0; i < count; ++i) {
        word_array[i] = malloc(sizeof(char) * (my_strlen(array) + 1));
        if (word_array[i] == NULL)
            return NULL;
        for (; array[pos] != '\n' && array[pos] != '\0'; ++j, ++pos)
            word_array[i][j] = array[pos];
        ++pos;
        word_array[i][j] = '\0';
        j = 0;
    }
    word_array[count] = NULL;
    return word_array;
}
