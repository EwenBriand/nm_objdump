/*
** EPITECH PROJECT, 2023
** nm
** File description:
** start_nm
*/

#include "my.h"

void my_obj(int fd, char *file)
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
        obj_32(buf, file);
    } else if (elf->e_ident[EI_CLASS] == ELFCLASS64)
        obj_64(elf, file);
    else
        printf("objdump: %s: file format not recognized\n", file);
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
            printf("objdump: %s: file format not recognized\n", file);
            return -1;
        } else
            return 0;
    } else {
        perror("mmap");
    }

    return 0;
}

static void make_obj(int fd, char *file)
{
    if (check_archi(fd, file) == -1) {
        return;
    }
    printf("\n");
    my_obj(fd, file);
}

static int make_multiple(int argc, char **argv)
{
    int fd = -1;
    int res = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-sf") || !strcmp(argv[i], "-fs"))
            continue;
        if ((fd = open(argv[i], O_RDONLY)) != -1) {
            make_obj(fd, argv[i]);
            continue;
        }
        printf("objdump: '%s': No such file\n", argv[i]);
        res = -1;
    }
    return res;
}

int start_obj(int argc, char **argv, int pos)
{
    int fd = -1;

    if (argc == 2)
        if ((fd = open("a.out", O_RDONLY)) != -1)
            my_obj(fd, "a.out");
        else {
            printf("objdump: '%s': No such file\n", "a.out");
            return 1;
        }
    if (argc == 3)
        if ((fd = open(argv[pos], O_RDONLY)) != -1)
            my_obj(fd, argv[pos]);
        else {
            printf("objdump: '%s': No such file\n", argv[pos]);
            return 1;
        }
    if (argc > 3 && make_multiple(argc, argv) == -1)
        return 1;
    return END_VALUE;
}
