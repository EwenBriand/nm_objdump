/*
** EPITECH PROJECT, 2023
** nm
** File description:
** sec_symtab
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

static void is_notype(Elf32_Sym *sym)
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

static void is_object(Elf32_Sym *sym, elf32_t *elf32)
{
    Elf32_Shdr *shdr;

    if (sym->st_shndx == SHN_UNDEF) {
        printf("U ");
    } else if (sym->st_shndx == SHN_COMMON) {
        printf("C ");
    } else {
        shdr = &elf32->shdr[sym->st_shndx];
        if (shdr->sh_type == SHT_NOBITS) {
            get_min_max(sym->st_info, shdr->sh_flags & SHF_WRITE ? 'b' : 'r');
        } else {
            get_min_max(sym->st_info, shdr->sh_flags & SHF_WRITE ? 'd' : 'r');
        }
    }
}

static void print_symbol_type32(elf32_t *elf32, int i)
{
    Elf32_Sym *sym = &elf32->sym[i];
    switch (ELF32_ST_TYPE(sym->st_info)) {
        case STT_NOTYPE: is_notype(sym); break;
        case STT_OBJECT: is_object(sym, elf32); break;
        case STT_FUNC: is_function32(sym, elf32); break;
        case STT_SECTION: printf("S "); break;
        case STT_FILE: printf("F "); break;
        default: printf("? "); break;
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
    print_symbol_type32(elf32, i);
    printf("%s\n", str + elf32->sym[i].st_name);
}
