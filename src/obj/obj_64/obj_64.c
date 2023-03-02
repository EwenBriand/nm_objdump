/*
** EPITECH PROJECT, 2023
** nm
** File description:
** obj_64
*/

#include "my.h"

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>

static int print_hexa(elf64_t *elf64, int *arg, char *buf2)
{
    unsigned char *section_data = (unsigned char *) ((char *) elf64->elf
        + elf64->shdr[arg[0]].sh_offset);
    unsigned int act = section_data[arg[1] + arg[3]];
    if ((unsigned long int) arg[1] + arg[3] >= elf64->shdr[arg[0]].sh_size) {
        printf("  ");
        buf2[arg[2]++] = ' ';
    } else {
        printf("%02x", act);
        if (act < 32 || act > 126)
            buf2[arg[2]++] = '.';
        else
            buf2[arg[2]++] = act;
    }
    return arg[2];
}

static void print_16_char(elf64_t *elf64, int i, int j)
{
    char buf2[18];
    int pos = 0;
    int args[4];
    for (size_t x = 0; x < 16; ++x) {
        if (x == 4 || x == 8 || x == 12)
            printf(" ");
        args[0] = i;
        args[1] = j;
        args[2] = pos;
        args[3] = x;
        pos = print_hexa(elf64, args, buf2);
    }
    buf2[pos] = '\0';
    printf("  %s\n", buf2);
}

static void print_section(elf64_t *elf64, int i)
{
    if (elf64->shdr[i].sh_addr != 0) {
        printf(
            "Contents of section %s:\n", &elf64->str[elf64->shdr[i].sh_name]);
        for (size_t j = 0; j < elf64->shdr[i].sh_size; j += 16) {
            printf(" %04lx ", elf64->shdr[i].sh_addr + j);
            print_16_char(elf64, i, j);
            // print_section_content(elf64->elf, &elf64->shdr[i]);
        }
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
