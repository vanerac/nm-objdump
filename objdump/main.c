/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <elf.h>
# include <sys/mman.h>
# include <sys/stat.h>
#include <unistd.h>
#include "../tools/tools.h"

void print_header(char *filename, void *buffer)
{
    GET_ELF_EHDR(buffer, e_type); // type
    GET_ELF_EHDR(buffer, e_entry); // entry point
    GET_ELF_EHDR(buffer, e_flags); // flags

    // file name: type
    // arch: arch type, flags : flags
    // start address
    // \n


}

void print_section(const char *name, void *addr)
{
    printf("Contents of section %s:\n", name);
    //    for (size_t i = 0; i < GET_ELF_SHDR(addr, sh_size); ++i) {
    //        if (!(i % 5) && i != 0)
    //            printf("\n");
    //        printf("%04lx ", GET_ELF_SHDR(addr, sh_addr));
    //
    //    }
    // todo hexdump nsm
    // todo filter sections to print
    printf("\n");
}

int main(int ac, char **ag)
{
    void *buffer;
    if (ac < 2)
        return 84;
    size_t size = parse_file(ag[1], &buffer);
    if (!size)
        return 84;
    is64arch = GET_ELF_EHDR(buffer, e_ident[EI_CLASS]);
    if (GET_ELF_EHDR(buffer, e_ident[EI_VERSION]) != EV_CURRENT)
        return 84;
    print_header(ag[1], buffer);

    void *tab_header = buffer + GET_ELF_EHDR(buffer, e_shoff) + (GET_ELF_EHDR
    (buffer, e_shentsize) * GET_ELF_EHDR(buffer, e_shstrndx));
    char *tab = buffer + GET_ELF_SHDR(tab_header, sh_offset);

    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        print_section(&tab[GET_ELF_SHDR(shdr, sh_name)], shdr);
    }
    munmap(buffer, size);
    return 0;
}