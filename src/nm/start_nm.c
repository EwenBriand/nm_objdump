/*
** EPITECH PROJECT, 2023
** nm
** File description:
** start_nm
*/

#include "my.h"

void my_nm(int fd, char *file)
{
    void *buf;
    Elf64_Ehdr *elf;
    struct stat s;

    fstat(fd, &s);
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf == NULL)
        return;
    elf = buf;
    if (elf->e_ident[EI_CLASS] == ELFCLASS32) {
        nm_32(buf, file);
    } else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
        nm_64(elf, file);
    else
        printf("nm: %s: file format not recognized\n", file);
}

static int check_archi(int fd, char *file)
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

static void make_nm(int fd, char *file)
{
    if (check_archi(fd, file) == -1) {
        return;
    }
    printf("\n");
    printf("%s:\n", file);
    my_nm(fd, file);
}

static int make_multiple(int argc, char **argv)
{
    int fd = -1;
    int res = 0;

    for (int i = 1; i < argc; i++) {
        if ((fd = open(argv[i], O_RDONLY)) != -1) {
            make_nm(fd, argv[i]);
        } else {
            printf("nm: '%s': No such file\n", argv[i]);
            res = -1;
        }
    }
    return res;
}

int start_nm(int argc, char **argv)
{
    int fd = -1;

    if (argc == 1)
        if ((fd = open("a.out", O_RDONLY)) != -1)
            my_nm(fd, "a.out");
        else {
            printf("nm: '%s': No such file\n", "a.out");
            return 1;
        }
    if (argc == 2)
        if ((fd = open(argv[1], O_RDONLY)) != -1)
            my_nm(fd, argv[1]);
        else {
            printf("nm: '%s': No such file\n", argv[1]);
            return 1;
        }
    if (argc > 2 && make_multiple(argc, argv) == -1)
        return 1;
    return END_VALUE;
}
