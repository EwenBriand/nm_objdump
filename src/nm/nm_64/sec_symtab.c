/*
** EPITECH PROJECT, 2023
** nm
** File description:
** sec_symtab
*/

#include <ctype.h>
#include "my.h"

static void get_min_max(unsigned char type, char ch)
{
    if (ELF64_ST_BIND(type) == STB_GLOBAL)
        printf("%c ", toupper(ch));
    else
        printf("%c ", ch);
}

static void is_section(elf64_t *elf64, int i)
{
    printf("IM IN %s\n",
        &elf64->str[elf64->shdr[elf64->sym[i].st_shndx].sh_name]);
    for (int j = 0; j < elf64->elf->e_shnum; ++j) {
        if (!strcmp(&elf64->str[elf64->shdr[elf64->sym[i].st_shndx].sh_name],
                &elf64->str[elf64->shdr[j].sh_name]))
            printf("IM IN %s\n", &elf64->str[elf64->shdr[j].sh_name]);
    }
}

static void print_type64(elf64_t *elf64, int i)
{
    int type = ELF64_ST_TYPE(elf64->sym[i].st_info);
    switch (type) {
        case STT_NOTYPE: return get_min_max(elf64->sym[i].st_info, '?');
        case STT_OBJECT: return get_min_max(elf64->sym[i].st_info, 'd');
        case STT_FUNC: return get_min_max(elf64->sym[i].st_info, 't');
        case STT_SECTION: return is_section(elf64, i);
        case STT_FILE: return get_min_max(elf64->sym[i].st_info, 'f');
        default: return get_min_max(elf64->sym[i].st_info, '?');
    }
}

void sec_symtab_64(elf64_t *elf64, int i)
{
    char buf[50];
    sprintf(buf, "%lx", elf64->sym[i].st_value);
    char *str = (char *) ((char *) elf64->elf + elf64->strtab->sh_offset);

    if (elf64->sym[i].st_name == 0)
        return;
    if (elf64->sym[i].st_value > 0) {
        for (int i = strlen(buf); i < 16; i++)
            printf("0");
        printf("%lx ", elf64->sym[i].st_value);
    } else
        printf("                 ");
    print_type64(elf64, i);
    printf("%s\n", str + elf64->sym[i].st_name);
}
