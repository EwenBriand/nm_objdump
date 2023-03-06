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
    if (ELF64_ST_BIND(type) == STB_WEAK)
        ch = 'w';
    if (ELF64_ST_BIND(type) == STB_GLOBAL)
        printf("%c ", toupper(ch));
    else
        printf("%c ", ch);
}

static void is_notype(Elf64_Sym *sym)
{
    if (sym->st_shndx == SHN_UNDEF) {
        get_min_max(sym->st_info, 'u');
        return;
    }
    if (sym->st_shndx == SHN_ABS) {
        get_min_max(sym->st_info, 'a');
        return;
    }
    if (sym->st_shndx == SHN_COMMON) {
        get_min_max(sym->st_info, 'c');
        return;
    }
    get_min_max(sym->st_info, 't');
}

static void is_object(Elf64_Sym *sym, elf64_t *elf64)
{
    Elf64_Shdr *shdr;

    if (sym->st_shndx == SHN_UNDEF) {
        printf("U ");
    } else if (sym->st_shndx == SHN_COMMON) {
        printf("C ");
    } else {
        shdr = &elf64->shdr[sym->st_shndx];
        if (shdr->sh_type == SHT_NOBITS) {
            get_min_max(sym->st_info, shdr->sh_flags & SHF_WRITE ? 'b' : 'r');
        } else {
            get_min_max(sym->st_info, shdr->sh_flags & SHF_WRITE ? 'd' : 'r');
        }
    }
}

static void print_symbol_type(elf64_t *elf64, int i)
{
    Elf64_Sym *sym = &elf64->sym[i];
    switch (ELF64_ST_TYPE(sym->st_info)) {
        case STT_NOTYPE: is_notype(sym); break;
        case STT_OBJECT: is_object(sym, elf64); break;
        case STT_FUNC: is_function(sym, elf64); break;
        case STT_SECTION: printf("S "); break;
        case STT_FILE: printf("F "); break;
        default: printf("? "); break;
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
    print_symbol_type(elf64, i);
    printf("%s\n", str + elf64->sym[i].st_name);
}
