/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** opener.c file
*/

#include <stddef.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zconf.h>
#include <stdbool.h>
#include <string.h>
#include "tools.h"

bool *is64architecture()
{
    static bool arch = 1;
    return &arch;
}

int error_check(size_t size, void *buffer)
{
    if (!size)
        return 1;
    if (GET_ELF_EHDR(buffer, e_ident[EI_VERSION]) != EV_CURRENT)
        return 1;
    return 0;
}

char *get_name(void *buffer, size_t index)
{
    void *tab_header = buffer + GET_ELF_EHDR(buffer, e_shoff) + (GET_ELF_EHDR
    (buffer, e_shentsize) * GET_ELF_EHDR(buffer, e_shstrndx));
    char *tab = buffer + GET_ELF_SHDR(tab_header, sh_offset);

    return &tab[index];
}

size_t parse_file(char *prog_name, char *path, void **buff)
{
    int fd;
    struct stat s;

    if ((fd = open(path, O_RDONLY)) < 0)
        return 0;
    fstat(fd, &s);
    *buff = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    int class = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]);
    int data = GET_ELF_EHDR(*buff, e_ident[EI_DATA]);
    IS64ARCH = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]) == 1 ? 0 : 1;

    if ((class != ELFCLASS64 && class != ELFCLASS32) ||
        (data != ELFDATA2LSB && data != ELFDATA2MSB) ||
        (GET_ELF_EHDR(*buff, e_shnum) * GET_ELF_EHDR(*buff, e_shentsize) +
            GET_ELF_EHDR(*buff, e_shoff) > s.st_size) ||
        strncmp((char *) *buff, "\x7f\x45\x4c\x46", 4) != 0) {
        fprintf(stderr, "%s: %s: %s\n", prog_name, path,
            "file format not recognized");
        return 0;
    }

    IS64ARCH = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]) == 1 ? 0 : 1;
    return s.st_size;
}