/*
** EPITECH PROJECT, 2023
** nm
** File description:
** print_type
*/

#include "my.h"

static void get_min_max(unsigned char type, char ch)
{
    if (ELF32_ST_BIND(type) == STB_WEAK)
        ch = 'w';
    if (ELF32_ST_BIND(type) == STB_GLOBAL)
        printf("%c ", toupper(ch));
    else
        printf("%c ", ch);
}

static void is_func2(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
    if (shdr->sh_flags & SHF_WRITE && shdr->sh_flags & SHF_ALLOC)
        get_min_max(sym->st_info, 'd');
    else if (shdr->sh_flags & SHF_EXECINSTR && shdr->sh_flags & SHF_ALLOC)
        get_min_max(sym->st_info, 't');
}

static void func3(Elf32_Sym *sym, elf32_t *elf32)
{
    Elf32_Shdr *shdr = &elf32->shdr[sym->st_shndx];
    if (shdr->sh_type == SHT_NOBITS)
        printf("%c ", shdr->sh_flags & SHF_WRITE ? 'b' : 'r');
    else if (shdr->sh_type == SHT_PROGBITS) {
        is_func2(sym, shdr);
    } else {
        get_min_max(sym->st_info, '?');
    }
}

void is_function32(Elf32_Sym *sym, elf32_t *elf32)
{
    if (sym->st_shndx == SHN_UNDEF) {
        printf("U ");
    } else {
        func3(sym, elf32);
    }
}
