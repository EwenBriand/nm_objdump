/*
** EPITECH PROJECT, 2021
** libmy.h
** File description:
** creat the header of the libmy.a
*/

#include <ctype.h>
#include <elf.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#ifndef _LIBALL_POOL
    #define _LIBALL_POOL

typedef struct elf64_s {
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf64_Shdr *symtab;
    Elf64_Shdr *strtab;
    Elf64_Sym *sym;
    int nb_sym;
    char *str;
    char *filename;
} elf64_t;

typedef struct elf32_s {
    Elf32_Ehdr *elf;
    Elf32_Shdr *shdr;
    Elf32_Shdr *symtab;
    Elf32_Shdr *strtab;
    Elf32_Sym *sym;
    int nb_sym;
    char *str;
    char *filename;
} elf32_t;

static const int ERROR_VALUE = 84;
static const int END_VALUE = 0;
static const char HELPER[] =
    "Usage: objdump <option(s)> <file(s)>\n"
    " Display information from object <file(s)>.\n"
    " At least one of the following switches must be given:\n"
    "  -a, --archive-headers    Display archive header information\n"
    "  -f, --file-headers       Display the contents of the overall file "
    "header\n"
    "  -p, --private-headers    Display object format specific file header "
    "contents\n"
    "  -P, --private=OPT,OPT... Display object format specific contents\n"
    "  -h, --[section-]headers  Display the contents of the section headers\n"
    "  -x, --all-headers        Display the contents of all headers\n"
    "  -d, --disassemble        Display assembler contents of executable "
    "sections\n"
    "  -D, --disassemble-all    Display assembler contents of all sections\n"
    "      --disassemble=<sym>  Display assembler contents from <sym>\n"
    "  -S, --source             Intermix source code with disassembly\n"
    "      --source-comment[=<txt>] Prefix lines of source code with <txt>\n"
    "  -s, --full-contents      Display the full contents of all sections "
    "requested\n"
    "  -g, --debugging          Display debug information in object file\n"
    "  -e, --debugging-tags     Display debug information using ctags style\n"
    "  -G, --stabs              Display (in raw form) any STABS info in the "
    "file\n"
    "  -W[lLiaprmfFsoORtUuTgAckK] or\n"
    "  "
    "--dwarf[=rawline,=decodedline,=info,=abbrev,=pubnames,=aranges,=macro,="
    "frames,\n"
    "          =frames-interp,=str,=str-offsets,=loc,=Ranges,=pubtypes,\n"
    "          =gdb_index,=trace_info,=trace_abbrev,=trace_aranges,\n"
    "          =addr,=cu_index,=links,=follow-links]\n"
    "                           Display DWARF info in the file\n"
    "  --ctf=SECTION            Display CTF info from SECTION\n"
    "  -t, --syms               Display the contents of the symbol table(s)\n"
    "  -T, --dynamic-syms       Display the contents of the dynamic symbol "
    "table\n"
    "  -r, --reloc              Display the relocation entries in the file\n"
    "  -R, --dynamic-reloc      Display the dynamic relocation entries in the "
    "file\n"
    "  @<file>                  Read options from <file>\n"
    "  -v, --version            Display this program's version number\n"
    "  -i, --info               List object formats and architectures "
    "supported\n"
    "  -H, --help               Display this information\n";

int my_strlen_int(int nb);
int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_revstr(char *str);
int my_putstr(char const *str);
void my_putnbr(int nb);
void my_putchar(char c);
char *get_buffer(char const *file);
char **make_word_array(char *array);

elf64_t *init_elf64(Elf64_Ehdr *ehdr, char *filename);
void delete_elf64(elf64_t *elf);
int start_nm(int argc, char **argv);
void nm_64(Elf64_Ehdr *elf, char *file);
void sec_symtab_64(elf64_t *elf64, int i);
void is_function(Elf64_Sym *sym, elf64_t *elf64);

elf32_t *init_elf32(Elf32_Ehdr *ehdr, char *filename);
void delete_elf32(elf32_t *elf);
void nm_32(Elf32_Ehdr *elf, char *file);
void sec_symtab_32(elf32_t *elf64, int i);
void is_function32(Elf32_Sym *sym, elf32_t *elf32);

int start_obj(int argc, char **argv, int pos);
void obj_64(Elf64_Ehdr *elf, char *file);
void obj_32(Elf32_Ehdr *elf, char *file);

#endif
