/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include <stddef.h>
#include "../tools/tools.h"

void print_sym(void *buffer, void *shdr)
{
    // start at shdr

    for (size_t i = 0;
        i < GET_ELF_SHDR(shdr, sh_size); i += GET_ELF_SHDR(shdr, sh_entsize)) {
        void *sym = (buffer + GET_ELF_SHDR(shdr, sh_offset) + i);
        size_t nm = GET_ELF_SYM(sym, st_name);
        size_t value = GET_ELF_SYM(sym, st_value);
        void *section = GET_ELF_SYM(sym, st_shndx);
        size_t size = GET_ELF_SYM(sym, st_size);
        //        size_t ref =

        // todo name isnt right
        printf("%016zx %zu %zu %zu: %s\n", value, size, nm, section,
            get_symbol_name(buffer, nm));
    }
}

int main(int ac, char **ag)
{
    void *buffer;
    if (ac < 2)
        return 84;
    size_t size = parse_file(ag[1], &buffer);
    if (!size)
        return 84;

    // cycle through sections
    // sh_type == SHT_SYMTAB

    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        printf("section name: %s\n",
            get_name(buffer, GET_ELF_SHDR(shdr, sh_name)));
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_SYMTAB) {
            print_sym(buffer, shdr);
        }
    }
    munmap(buffer, size);
}