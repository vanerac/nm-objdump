/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** opener.h file
*/

#ifndef C_TOOLS_H
#define C_TOOLS_H

#include <stdbool.h>
#include <stddef.h>
# include <fcntl.h>
# include <stdio.h>
# include <elf.h>
# include <sys/mman.h>
# include <sys/stat.h>
#include <unistd.h>

bool *is64architecture(void);

#define IS64ARCH        (*is64architecture())

#define GET_ELF_EHDR(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Ehdr *)__buff)->__var_name      \
                        :   ((Elf32_Ehdr *)__buff)->__var_name)

#define GET_ELF_SHDR(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Shdr *)__buff)->__var_name      \
                        :   ((Elf32_Shdr *)__buff)->__var_name)

#define GET_ELF_SYM(__buff, __var_name)        (IS64ARCH ?         \
                            ((Elf64_Sym *)__buff)->__var_name      \
                        :   ((Elf32_Sym *)__buff)->__var_name)

char *get_name(void *buffer, size_t index);

char *get_symbol_name(void *buffer, size_t index);

int error_check(size_t size, void *buffer);

size_t parse_file(char *prog_name, char *path, void **buff);

#endif //C_TOOLS_H
