/*
** EPITECH PROJECT, 2021
** libmy.h
** File description:
** creat the header of the libmy.a
*/

#include <elf.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#ifndef _LIBALL_POOL
    #define _LIBALL_POOL

typedef struct elf64_s {
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *sym;
    char *str;
    char *filename;
} elf64_t;

static const int ERROR_VALUE = 84;
static const int END_VALUE = 0;

int my_strlen_int(int nb);
int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_revstr(char *str);
int my_putstr(char const *str);
void my_putnbr(int nb);
void my_putchar(char c);
char *get_buffer(char const *file);
char **make_word_array(char *array);

elf64_t *init_elf64(Elf64_Ehdr *ehdr, char *filename);
void delete_elf64(elf64_t *elf);

#endif
