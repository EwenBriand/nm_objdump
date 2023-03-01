/*
** EPITECH PROJECT, 2023
** nm
** File description:
** init_delete
*/

#include "my.h"

elf32_t *init_elf32(Elf32_Ehdr *ehdr, char *filename)
{
    elf32_t *elf = malloc(sizeof(elf32_t));

    if (elf == NULL)
        return NULL;
    elf->elf = ehdr;
    elf->shdr = (Elf32_Shdr *) ((char *) ehdr + ehdr->e_shoff);
    elf->str =
        (char *) ((char *) ehdr + elf->shdr[ehdr->e_shstrndx].sh_offset);
    elf->filename = filename;
    return elf;
}

void delete_elf32(elf32_t *elf)
{
    free(elf);
}
