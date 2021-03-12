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

void print_header(char *filename, void *buffer)
{
    int type = GET_ELF_EHDR(buffer, e_type);
    unsigned int flags = 0;
    flags = type == ET_EXEC ? (EXEC_P | D_PAGED) : flags;
    flags = type == ET_DYN ? (DYNAMIC | D_PAGED) : flags;
    flags = type == ET_REL ? HAS_RELOC : flags;
    for (int i = 0; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        if (GET_ELF_SHDR(shdr, sh_type) == SHT_SYMTAB) {
            flags = flags | HAS_SYMS;
            break;
        }
    }
    printf("\n%s:\tfile format %s\n", filename,
        IS64ARCH ? "elf64-x86-64" : "elf32-i386");
    printf("architecture: %s, ", "i386:x86-64");
    printf("flags 0x%08x:\n", flags);
    printf("start address 0x%016lx\n\n", GET_ELF_EHDR(buffer, e_entry));
}

void print_text(unsigned char *str, int size)
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
    printf("\n");
}

void print_section(const char *name, void *buffer, void *addr)
{
    if (!GET_ELF_SHDR(addr, sh_size))
        return;
    printf("Contents of section %s:\n", name);
    unsigned char *add = buffer + GET_ELF_SHDR(addr, sh_offset);
    size_t i = 0;
    for (; i < GET_ELF_SHDR(addr, sh_size); ++i) {
        if (!(i % 16) && i != 0)
            print_text(&add[i - 16], 16);
        if (!(i % 16))
            printf(" %04lx", GET_ELF_SHDR(addr, sh_addr) + i);
        if (!(i % 4))
            printf(" ");
        printf("%02x", add[i]);
    }
    unsigned short diff = (i % 16);
    for (unsigned short index = 0;
        diff && index < ((16 - diff) * 2 + (16 - diff) / 4); ++index)
        printf(" ");
    diff = !diff ? 16 : diff;
    print_text(&add[i - diff], diff);
}

int my_objdump(char *prog_name, char *name)
{
    void *buffer;

    size_t size = parse_file(prog_name, name, &buffer);
    if (error_check(size, buffer)) {
        munmap(buffer, size);
        return 84;
    }
    print_header(name, buffer);

    for (int i = 1; i < GET_ELF_EHDR(buffer, e_shnum); ++i) {
        void *shdr = (buffer + GET_ELF_EHDR(buffer, e_shoff)) + (GET_ELF_EHDR
        (buffer, e_shentsize) * i);
        print_section(get_name(buffer, GET_ELF_SHDR(shdr, sh_name)), buffer,
            shdr);
    }
    munmap(buffer, size);
    return 0;
}

int main(int ac, char **ag)
{
    if (ac < 2)
        return my_objdump(ag[0], "a.out");
    int ret = 0;
    for (int i = 1; i < ac; ++i)
        ret += my_objdump(ag[0], ag[i]);

    return ret != 0 ? 84 : 0;
}