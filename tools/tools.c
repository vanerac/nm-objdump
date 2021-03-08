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
#include "tools.h"

bool *is64architecture()
{
    static bool arch = 2;
    return &arch;
}

char *get_name(void *buffer, size_t index)
{
    void *tab_header = buffer + GET_ELF_EHDR(buffer, e_shoff) + (GET_ELF_EHDR
        (buffer, e_shentsize) * GET_ELF_EHDR(buffer, e_shstrndx));
    char *tab = buffer + GET_ELF_SHDR(tab_header, sh_offset);

    return &tab[index];
}

size_t parse_file(char *path, void **buff)
{
    int fd;
    struct stat s;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return 0;
    fstat(fd, &s);
    *buff = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    is64arch = GET_ELF_EHDR(*buff, e_ident[EI_CLASS]);
    return s.st_size;
}