/*
** EPITECH PROJECT, 2022
** my project
** File description:
** main
*/

#include "my.h"

int get_min_or_max(unsigned char type)
{
    if (ELF64_ST_TYPE(type) == STB_LOCAL)
        return 1;
    if (ELF64_ST_TYPE(type) == STB_GLOBAL)
        return 0;
    return -1;
}

char get_64_type(unsigned char type)
{
    return 'T';
}

// int elf64_print_name(Elf64_Sym *sym, Elf64_Ehdr *elf, Elf64_Shdr *shdr)
void elf64_print(elf64_t *elf64, int i)
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
    printf("%i ", ELF64_ST_TYPE(elf64->sym[i].st_info));
    printf("%s\n", str + elf64->sym[i].st_name);
}

// void nm_64_symbol(Elf64_Sym *sym, Elf64_Ehdr *elf, Elf64_Shdr *sec)
void nm_64_symbol(elf64_t *elf64, int i)
{
    printf("%s\n", &elf64->str[elf64->shdr[i].sh_name]);
    if (strcmp(&elf64->str[elf64->shdr[i].sh_name], ".symtab") == 0)
        elf64->symtab = (Elf64_Shdr *) &elf64->shdr[i];
    if (strcmp(&elf64->str[elf64->shdr[i].sh_name], ".strtab") == 0)
        elf64->strtab = (Elf64_Shdr *) &elf64->shdr[i];

    // Elf64_Sym *new;
    // for (uint16_t i = 0; i < sec->sh_offset / sizeof(Elf64_Sym); i++) {
    //     new = (Elf64_Sym *) ((char *) sym + (i * sizeof(Elf64_Sym)));
    //     if (new->st_name != 0)
    //         return;
    // elf64_print_name(new, elf, sec);
    // printf("symbol '%s' is the %i symbol of the '%s' section\n",
    //     (char *) ((char *) elf + ((char *) new)[elf->e_shstrndx]), i,
    //     (char *) ((char *) elf + ((char *) sec)[elf->e_shstrndx]));
}

void nm_64(Elf64_Ehdr *elf, char *file)
{
    elf64_t *elf64 = init_elf64(elf, file);

    // elf64_print_name(elf);
    if (elf64->elf->e_type != ET_DYN && elf64->elf->e_type != ET_EXEC
        && elf64->elf->e_type != ET_REL) {
        printf("nm: %s: file format not recognized\n", elf64->filename);
        return;
    }
    printf("64-bit architecture\n");
    for (int i = 0; i < elf64->elf->e_shnum; ++i)
        if (elf64->shdr[i].sh_size)
            nm_64_symbol(elf64, i);

    elf64->sym =
        (Elf64_Sym *) ((char *) elf64->elf + elf64->symtab->sh_offset);
    for (size_t i = 0; i < elf64->symtab->sh_size / sizeof(Elf64_Sym); i++)
        elf64_print(elf64, i);
    delete_elf64(elf64);
}

void my_nm(int fd, char *file)
{
    void *buf;
    Elf64_Ehdr *elf;
    struct stat s;

    fstat(fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf != NULL) {
        elf = buf;
        if (elf->e_ident[EI_CLASS] == ELFCLASS32)
            printf("32-bit architecture\n");
        else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
            nm_64(elf, file);
        else
            printf("nm: %s: file format not recognized\n", file);
    } else {
        perror("mmap");
    }
}

int check_archi(int fd, char *file)
{
    void *buf;
    Elf64_Ehdr *elf;
    struct stat s;

    fstat(fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf != NULL) {
        elf = buf;
        if (elf->e_ident[EI_CLASS] != ELFCLASS32
            && elf->e_ident[EI_CLASS] != ELFCLASS64) {
            printf("nm: %s: file format not recognized\n", file);
            return -1;
        } else
            return 0;
    } else {
        perror("mmap");
    }

    return 0;
}

void make_nm(int fd, char *file)
{
    if (check_archi(fd, file) == -1) {
        return;
    }
    printf("\n");
    printf("%s:\n", file);
    my_nm(fd, file);
}

int make_multiple(int argc, char **argv)
{
    int fd = -1;

    for (int i = 1; i < argc; i++) {
        if ((fd = open(argv[i], O_RDONLY)) != -1) {
            make_nm(fd, argv[i]);
        } else {
            printf("nm: '%s': No such file\n", argv[i]);
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    int fd = -1;

    if (env[0] == NULL)
        return ERROR_VALUE;

    if (argc == 1)
        if ((fd = open("a.out", O_RDONLY)) != -1)
            my_nm(fd, "a.out");
        else {
            printf("nm: '%s': No such file\n", "a.out");
            return 1;
        }
    else if (argc == 2)
        if ((fd = open(argv[1], O_RDONLY)) != -1)
            my_nm(fd, argv[1]);
        else {
            printf("nm: '%s': No such file\n", argv[1]);
            return 1;
        }
    else if (make_multiple(argc, argv) == -1)
        return 1;

    return END_VALUE;
}

// not exist = nm: 'helo': No such file
// not format = nm: bs/about1.c: file format not recognized
// section -> symbol -> info
// get archi : e_ident -> EI_CLASS -> ELFCLASS32/64

// e_shoff -> pointeur vers les section
// e_shnum -> nombre de section
// e_shentsize -> taille d'une section

// e_shstrndx -> pointeur de la section nom
// sh_name -> index du nom de la section

// each section have a pointer and the number of symbol (sh_offset,
// sh_size) sh_type -> find if it's a symbol table
