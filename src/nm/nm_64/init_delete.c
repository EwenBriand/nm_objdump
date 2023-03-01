/*
** EPITECH PROJECT, 2023
** nm
** File description:
** init_delete
*/

#include "my.h"

elf64_t *init_elf64(Elf64_Ehdr *ehdr, char *filename)
{
    elf64_t *elf = malloc(sizeof(elf64_t));

    if (elf == NULL)
        return NULL;
    elf->elf = ehdr;
    elf->shdr = (Elf64_Shdr *) ((char *) ehdr + ehdr->e_shoff);
    elf->str =
        (char *) ((char *) ehdr + elf->shdr[ehdr->e_shstrndx].sh_offset);
    elf->filename = filename;
    return elf;
}

void delete_elf64(elf64_t *elf)
{
    free(elf);
}
