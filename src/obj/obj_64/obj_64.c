/*
** EPITECH PROJECT, 2023
** nm
** File description:
** obj_64
*/

#include "my.h"

static void print_section(elf64_t *elf64, int i)
{
    char buf2[18];
    int pos = 0;

    printf("Contents of section %s:\n", &elf64->str[elf64->shdr[i].sh_name]);
    for (size_t j = 0; j < elf64->shdr[i].sh_size; j += 16) {
        pos = 0;
        printf("%04lx ", elf64->shdr[i].sh_addr + j);
        for (int x = 0; x < 16; ++x) {
            if (x == 4 || x == 8 || x == 12)
                printf(" ");
            printf("%02lx", (char) elf64->shdr[i].sh_addr + j + x);
            if ((int) elf64->shdr[i].sh_addr + j + x < 32
                || (int) elf64->shdr[i].sh_addr + j + x > 126)
                buf2[pos++] = '.';
            else
                buf2[pos++] = (char) elf64->shdr[i].sh_addr + j + x;
        }
        buf2[pos] = '\0';
        printf(" %s\n", buf2);
    }
}

void obj_64(Elf64_Ehdr *elf, char *file)
{
    elf64_t *elf64 = init_elf64(elf, file);

    if (elf64->elf->e_type != ET_DYN && elf64->elf->e_type != ET_EXEC
        && elf64->elf->e_type != ET_REL) {
        printf("nm: %s: file format not recognized\n", elf64->filename);
        return;
    }
    printf("%i\n", elf64->elf->e_shnum);
    for (int i = 0; i < elf64->elf->e_shnum; ++i)
        if (elf64->shdr[i].sh_size)
            print_section(elf64, i);
    delete_elf64(elf64);
}
