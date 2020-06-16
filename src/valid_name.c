//
// Created by asipes on 16.06.2020.
//
#include "corewar.h"

int     valid_name(int size_arg, char* name_champ)
{
    int name_len;

    if(size_arg == 2)
    {
        // проверка что у файла есть имя и нужное расширение
        if((name_len = ft_strlen(name_champ)) > 2)
        {
            if(ft_strcmp(&name_champ[name_len - 2], CHAMP_EXP) == 0)
            {
                return (1);
            }
            else
            {
                ft_printf(EXTENSION_ERROR);
            }
        }
        else
        {
            ft_printf(EXTENSION_ERROR);
        }
    }
    else
    {
        // возможно неверное сообщение об ошибке
        ft_printf(CHAMP_COUNT_ERROR);
    }
    return (0);
}

