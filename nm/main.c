/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include <stddef.h>
#include "../tools/tools.h"

char symbol_type(size_t value, int type, int bind)
{
    char ret = '?';

    // todo add
    //  d => initalised data
    //  r => read only data
    //  w => weak but not an object type
    //  u -> function global & ndx != 0 (addr null), else t
    //  b =>
    switch (type) {
    case STT_NOTYPE:
        ret = 'd';
        break;
    case STT_OBJECT:
        ret = 'b';
        break;
    case STT_FUNC:
        if (!value)
            ret = 'u';
        else ret = 't';
        break;
//    case STT_SECTION:
//        ret = 's';
//        break;
//    case STT_FILE:
//        ret = '-';
//        break;
    default:
        return '?';
    }
    ret += bind == STB_GLOBAL ? 'a' - 'A' : 0;
    return ret;
}

void print_sym(void *buffer, void *shdr)
{

    for (size_t i = 0;
        i < GET_ELF_SHDR(shdr, sh_size); i += GET_ELF_SHDR(shdr, sh_entsize)) {


        void *sym = (buffer + GET_ELF_SHDR(shdr, sh_offset) + i);

        size_t nm = GET_ELF_SYM(sym, st_name);

        size_t value = GET_ELF_SYM(sym, st_value);

        int visibility =
            !IS64ARCH ? ELF32_ST_VISIBILITY(GET_ELF_SYM(sym, st_other)) :
                ELF32_ST_VISIBILITY(GET_ELF_SYM(sym, st_other));

        if (visibility != STV_DEFAULT)
            continue;
        int type = !IS64ARCH ? ELF32_ST_TYPE(GET_ELF_SYM(sym, st_info)) :
            ELF64_ST_TYPE(GET_ELF_SYM(sym, st_info));
        int bind = !IS64ARCH ? ELF32_ST_BIND(GET_ELF_SYM(sym, st_info)) :
            ELF64_ST_BIND(GET_ELF_SYM(sym, st_info));

        if (type == STT_FILE)
            continue;;

        printf("%016zx %c %s\n", value, symbol_type(value, type, bind),
            get_symbol_name(buffer, nm));
    }
}

int main(int ac, char **ag)
{
    void *buffer;
    if (ac < 2)
        return 84;
    size_t size = parse_file(ag[1], &buffer);
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
}