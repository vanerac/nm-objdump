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

bool *is64architecture()
{
    static bool arch = 2;
    return &arch;
}

char *get_name(void *buffer, size_t index)
{
    return NULL;
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
    return s.st_size;
}