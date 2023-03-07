/*
** EPITECH PROJECT, 2022
** my project
** File description:
** main
*/

#include "my.h"

int error_handler(int argc, char **argv)
{
    if (argc < 2
        || (argc == 2
            && (strcmp(argv[1], "-s") != 0 || strcmp(argv[1], "-sf") != 0
                || strcmp(argv[1], "-fs") != 0))) {
        printf("%s", HELPER);
        return -1;
    }

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[1], "-sf") == 0 || strcmp(argv[1], "-fs") == 0)
            return (i == 1) ? 2 : 1;
    return -1;
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
