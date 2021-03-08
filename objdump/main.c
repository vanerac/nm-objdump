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

    // todo flags print


}

void print_text(char *str, int size)
{
    printf("\t");
    for (int i = 0; i < size; ++i) {
        if (str[i] >= 32 && str[i] <= 127)
            printf("%c", str[i]);
        else
            printf(".");
    }
}

void print_section(const char *name, void *buffer, void *addr)
{
    printf("Contents of section %s:\n", name);
    unsigned char *add = buffer + GET_ELF_SHDR(addr, sh_offset);
    size_t i = 0;
    for (; i < GET_ELF_SHDR(addr, sh_size); ++i) {

        if (!(i % 16) && i != 0) {
            print_text(&add[i - 16], 16);
            printf("\n");
        }

        if (!(i % 4))
            printf(" ");

        printf("%02x", add[i]);
    }

    int rest = i % 16;
    //    for (int index = rest; index < 16; ++index)
    //    printf("\n%zu %lu\n", i, (i / (16 * 4)));
    for (int index = i; index % (16 * 2); ++index) {
        // todo fix alignment
        printf(" ");
    }

    print_text(&add[i - rest], rest);

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
    if (GET_ELF_EHDR(buffer, e_ident[EI_VERSION]) != EV_CURRENT)
        return 84;
    print_header(ag[1], buffer);

    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        print_section(get_name(buffer, GET_ELF_SHDR(shdr, sh_name)), buffer,
            shdr);
    }
    munmap(buffer, size);
    return 0;
}