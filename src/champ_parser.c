//
// Created by asipes on 16.06.2020.
//
#include "corewar.h"

int     champ_parser(char *champ_file)
{
    int gnl;
    int fd;
    char *line;

    fd = open(champ_file, O_RDONLY);
    while (get_next_line(fd, &line) == 1)
    {
        ft_printf("%s\n", line);
    }
    close(fd);
    return (0);
}
