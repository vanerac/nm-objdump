/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** main.c file
*/

#include <stddef.h>
# include <stdio.h>
# include <elf.h>
# include <sys/mman.h>
#include "../flags.h"
#include "../tools/tools.h"

int has_syms(void *buffer)
{
    // cycle through
}

void print_header(char *filename, void *buffer)
{
    int type = GET_ELF_EHDR(buffer, e_type);
    if (type | EXEC_P)
        printf("exec \n");
    if (type | HAS_SYMS)
        printf("sysm \n");
    if (type | D_PAGED)
        printf("DPAGED\n");

    printf("\n%s:\tfile format %s\n", filename,
        IS64ARCH ? "elf64-x86-64" : "elf32-i386");
    printf("architecture: %s,", "TODO"); // todo
    printf("flags 0x%08x:\n", type); //  TODO for flags, get program header
    printf("start address 0x%016lx\n\n", GET_ELF_EHDR(buffer, e_entry));

    // todo flags print


}

void print_text(char *str, int size)
{
    printf("\t");
    for (int i = 0; i < size; ++i) {
        if (str[i] >= 32 && str[i] < 127)
            printf("%c", str[i]);
        else
            printf(".");
    }
    int diff = 16 - size;
    for (int i = 0; i < diff; ++i)
        printf(" ");
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

    unsigned long diff = (i % 16);
    for (unsigned long index = 0;
        diff && index < ((16 - diff) * 2 + (16 - diff) / 4); ++index)
        printf(" ");

    print_text(&add[i - diff], diff);

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