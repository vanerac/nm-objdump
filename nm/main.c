/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include <stddef.h>
#include <string.h>
#include "../tools/tools.h"

char *get_symbol_name(void *buffer, size_t index)
{
    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        char *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_STRTAB &&
            GET_ELF_SHDR(shdr, sh_flags) == 0) {
            char *tab = buffer + GET_ELF_SHDR(shdr, sh_offset);
            return &tab[index];
        }
    }

    return NULL;
}

void print_sym(void *buffer, void *shdr)
{
    for (size_t i = 0;
        i < GET_ELF_SHDR(shdr, sh_size); i += GET_ELF_SHDR(shdr, sh_entsize)) {

        void *sym = (buffer + GET_ELF_SHDR(shdr, sh_offset) + i);
        size_t nm = GET_ELF_SYM(sym, st_name);
        size_t value = GET_ELF_SYM(sym, st_value);

        if (!IS64ARCH ? ELF32_ST_TYPE(GET_ELF_SYM(sym, st_info)) :
            ELF64_ST_TYPE(GET_ELF_SYM(sym, st_info)) == STT_FILE ||
                !strlen(get_symbol_name(buffer, nm)))
            continue;
        if (value)
            printf("%016zx", value);
        else
            printf("                ");
        printf(" %c %s\n", '?', get_symbol_name(buffer, nm));
    }
}

int my_nm(char *prog_name, char *path)
{
    void *buffer;

    size_t size = parse_file(prog_name, path, &buffer);
    if (error_check(size, buffer)) {
        munmap(buffer, size);
        return 84;
    }

    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_SYMTAB) {
            print_sym(buffer, shdr);
        }
    }
    munmap(buffer, size);
    return 0;
}

int main(int ac, char **ag)
{
    if (ac < 2)
        return my_nm(ag[0], "a.out");
    int ret = 0;
    for (int i = 1; i < ac; ++i)
        ret += my_nm(ag[0], ag[i]);

    return ret != 0 ? 84 : 0;
}