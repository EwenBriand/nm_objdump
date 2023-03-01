/*
** EPITECH PROJECT, 2023
** nm
** File description:
** sec_symtab
*/

#include "my.h"

static void get_min_or_max(unsigned char type, char ch)
{
    if (ELF32_ST_TYPE(type) == STB_LOCAL)
        printf("%c ", ch - 32);
    else if (ELF32_ST_TYPE(type) == STB_GLOBAL)
        printf("%c ", ch);
}

// int is_in_sec(char *name, Elf32_Shdr *tmp, elf32_t *elf32)
// {
//     char **act = ((char *) elf32->elf + elf32->symtab->sh_offset);
//     for (size_t j = 0; j < tmp->sh_size / sizeof(char *); j++) {
//         printf("%s = %s\n", name, act[j]);
//         if (strncmp(name, act[j], tmp->sh_size) == 0)
//             return 1;
//     }
//     return 0;
// }

static void print_type32(elf32_t *elf32, int i)
{
    // int type = ELF32_ST_TYPE(elf32->sym[i].st_info);
    // Elf32_Shdr *tmp;
    // for (int i = 0; i < elf32->elf->e_shnum; ++i) {
    //     tmp = (Elf32_Shdr *) &elf32->shdr[i];
    //     if (type == tmp->sh_type
    //         && is_in_sec(elf32->sym[i].st_value, tmp, elf32) == 1)
    //         printf("%s in ", &elf32->str[tmp->sh_name]);
    // }
    int type = ELF32_ST_TYPE(elf32->sym[i].st_info);
    switch (type) {
        case SHT_PROGBITS: get_min_or_max(elf32->sym[i].st_info, 'd'); break;
        case SHT_SYMTAB: get_min_or_max(elf32->sym[i].st_info, 't'); break;
        case SHT_NOBITS: get_min_or_max(elf32->sym[i].st_info, 'b'); break;
        default: get_min_or_max(elf32->sym[i].st_info, 't'); break;
    }
}

void sec_symtab_32(elf32_t *elf32, int i)
{
    char buf[50];
    sprintf(buf, "%x", elf32->sym[i].st_value);
    char *str = (char *) ((char *) elf32->elf + elf32->strtab->sh_offset);

    if (elf32->sym[i].st_name == 0)
        return;
    if (elf32->sym[i].st_value > 0) {
        for (int i = strlen(buf); i < 16; i++)
            printf("0");
        printf("%x ", elf32->sym[i].st_value);
    } else
        printf("                 ");
    print_type32(elf32, i);
    printf("%s\n", str + elf32->sym[i].st_name);
}
