/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm_32
*/

#include "my.h"

static void nm_32_symbol(elf32_t *elf32, int i)
{
    if (strcmp(&elf32->str[elf32->shdr[i].sh_name], ".strtab") == 0)
        elf32->strtab = (Elf32_Shdr *) &elf32->shdr[i];
    else if (strcmp(&elf32->str[elf32->shdr[i].sh_name], ".symtab") == 0)
        elf32->symtab = (Elf32_Shdr *) &elf32->shdr[i];
}

void nm_32(Elf32_Ehdr *elf, char *file)
{
    elf32_t *elf32 = init_elf32(elf, file);

    if (elf32->elf->e_type != ET_DYN && elf32->elf->e_type != ET_EXEC
        && elf32->elf->e_type != ET_REL) {
        printf("nm: %s: file format not recognized\n", elf32->filename);
        return;
    }
    printf("32-bit architecture\n");
    for (int i = 0; i < elf32->elf->e_shnum; ++i)
        if (elf32->shdr[i].sh_size)
            nm_32_symbol(elf32, i);

    elf32->sym =
        (Elf32_Sym *) ((char *) elf32->elf + elf32->symtab->sh_offset);
    for (size_t j = 0; j < elf32->symtab->sh_size / sizeof(Elf32_Sym); j++)
        sec_symtab_32(elf32, j);
    delete_elf32(elf32);
}
