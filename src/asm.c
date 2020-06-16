//
// Created by asipes on 16.06.2020.
//
#include "corewar.h"

int     main(int argc, char **argv)
{
    if(!valid_name(argc, argv[1]))
        return 0;
    champ_parser(argv[1]);
    return 0;
}
