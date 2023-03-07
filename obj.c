/*
** EPITECH PROJECT, 2022
** my project
** File description:
** main
*/

#include "my.h"

int error_handler(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[1], "-sf") == 0 || strcmp(argv[1], "-fs") == 0)
            return (i == 1) ? 2 : 1;
    return 0;
}

int main(int argc, char **argv, char **env)
{
    int res = error_handler(argc, argv);
    if (env[0] == NULL)
        return ERROR_VALUE;

    if (res == -1)
        return ERROR_VALUE;
    return start_obj(argc, argv, res);
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

// SHN_ABS -> abs val
// SHN_COMMON -> common val

// SHT_PROGBITS d/D, g/G, t/T, N, n,
