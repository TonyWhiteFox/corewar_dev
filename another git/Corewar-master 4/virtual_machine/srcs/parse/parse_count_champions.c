/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_champions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 21:26:27 by dhojt             #+#    #+#             */
/*   Updated: 2018/06/13 19:31:46 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				parse_count_champions(t_vm *vm)
{
	int				largest_num;
	t_champ			*champ;
	int				i;

	i = 0;
	largest_num = 0;
	champ = vm->champ;
	while (champ)
	{
		i++;
		if (champ->number > largest_num)
			largest_num = champ->number;
		champ = champ->next;
	}
	if (i > MAX_PLAYERS)
		error_exit(vm, "Too many Champions");
}
