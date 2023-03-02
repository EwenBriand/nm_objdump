/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm_64
*/

#include "my.h"

static void nm_64_symbol(elf64_t *elf64, int i)
{
    if (strcmp(&elf64->str[elf64->shdr[i].sh_name], ".strtab") == 0)
        elf64->strtab = (Elf64_Shdr *) &elf64->shdr[i];
    else if (strcmp(&elf64->str[elf64->shdr[i].sh_name], ".symtab") == 0)
        elf64->symtab = (Elf64_Shdr *) &elf64->shdr[i];
}

void nm_64(Elf64_Ehdr *elf, char *file)
{
    elf64_t *elf64 = init_elf64(elf, file);

    if (elf64->elf->e_type != ET_DYN && elf64->elf->e_type != ET_EXEC
        && elf64->elf->e_type != ET_REL) {
        printf("nm: %s: file format not recognized\n", elf64->filename);
        return;
    }
    for (int i = 0; i < elf64->elf->e_shnum; ++i)
        if (elf64->shdr[i].sh_size)
            nm_64_symbol(elf64, i);

    elf64->sym =
        (Elf64_Sym *) ((char *) elf64->elf + elf64->symtab->sh_offset);
    for (size_t j = 0; j < elf64->symtab->sh_size / sizeof(Elf64_Sym); j++)
        sec_symtab_64(elf64, j);
    delete_elf64(elf64);
}
