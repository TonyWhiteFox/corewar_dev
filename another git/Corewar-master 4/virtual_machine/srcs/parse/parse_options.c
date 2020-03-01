/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:05:21 by dhojt             #+#    #+#             */
/*   Updated: 2018/06/21 16:03:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				parse_options(t_vm *vm)
{
	int				i;
	char			**argv;

	i = 1;
	argv = vm->argv;
	while (argv[i])
	{
		parse_dump(vm, argv, i);
		parse_debug(vm, argv, i);
		parse_num(vm, argv, i);
		parse_aff(vm, argv, i);
		i++;
	}
	parse_check_dump_debug(vm);
}
