/*
** EPITECH PROJECT, 2022
** my project
** File description:
** main
*/

#include <elf.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "my.h"

void my_nm(int fd)
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
            printf("64-bit architecture\n");
    } else {
        perror("mmap");
    }
    // struct stat buffer;
    // int status = fstat(fileno(fd), &buffer);
    // if (status == 0) {
    //     if (buffer.st_size > 32767) {
    //         printf("64-bit architecture\n");
    //     } else {
    //         printf("32-bit architecture\n");
    //     }
    // } else {
    //     return;
    // }
}

int make_multiple(int argc, char **argv)
{
    int fd = -1;

    for (int i = 1; i < argc; i++) {
        if ((fd = open(argv[i], O_RDONLY)) != -1) {
            printf("%s:\n", argv[i]);
            my_nm(fd);
            if (i != argc - 1)
                printf("\n");
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

    if (argc == 2)
        if ((fd = open(argv[1], O_RDONLY)) != -1)
            my_nm(fd);
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
