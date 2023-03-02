/*
** EPITECH PROJECT, 2023
** nm
** File description:
** obj_32
*/

#include "my.h"

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>

static int print_hexa(elf32_t *elf32, int *arg, char *buf2)
{
    unsigned char *section_data = (unsigned char *) ((char *) elf32->elf
        + elf32->shdr[arg[0]].sh_offset);
    unsigned int act = section_data[arg[1] + arg[3]];
    if ((unsigned long int) arg[1] + arg[3] >= elf32->shdr[arg[0]].sh_size) {
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

static void print_16_char(elf32_t *elf32, int i, int j)
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
        pos = print_hexa(elf32, args, buf2);
    }
    buf2[pos] = '\0';
    printf("  %s\n", buf2);
}

static void print_section(elf32_t *elf32, int i)
{
    if (elf32->shdr[i].sh_addr != 0) {
        printf(
            "Contents of section %s:\n", &elf32->str[elf32->shdr[i].sh_name]);
        for (size_t j = 0; j < elf32->shdr[i].sh_size; j += 16) {
            printf(" %04lx ", elf32->shdr[i].sh_addr + j);
            print_16_char(elf32, i, j);
        }
    }
}

void obj_32(Elf32_Ehdr *elf, char *file)
{
    elf32_t *elf32 = init_elf32(elf, file);

    if (elf32->elf->e_type != ET_DYN && elf32->elf->e_type != ET_EXEC
        && elf32->elf->e_type != ET_REL) {
        printf("nm: %s: file format not recognized\n", elf32->filename);
        return;
    }
    printf("%i\n", elf32->elf->e_shnum);
    for (int i = 0; i < elf32->elf->e_shnum; ++i)
        if (elf32->shdr[i].sh_size)
            print_section(elf32, i);
    delete_elf32(elf32);
}
