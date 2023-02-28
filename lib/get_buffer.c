/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** get_buffer
*/

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "my.h"

static int my_file_len(char const *name)
{
    int fd = open(name, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
    char buff[2];
    int offset = 0;
    int len = 1;

    if (fd == -1)
        return -1;
    while (len != 0) {
        len = read(fd, buff, 1);
        ++offset;
    }
    if (close(fd) == -1)
        return -1;
    return offset;
}

char *get_buffer(char const *file)
{
    int fd = open(file, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
    int len = my_file_len(file);
    char *buffer = NULL;

    if (len == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (len));
    if (buffer == NULL)
        return NULL;
    if (fd == -1)
        return NULL;
    len = read(fd, buffer, len);
    if (close(fd) == -1) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}
