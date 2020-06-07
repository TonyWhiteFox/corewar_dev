/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:38:33 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/03/19 18:09:45 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool		find_dump_vis_flags(t_main *m, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-dump") && *i + 2 < ac && is_number(av[*i + 1]))
	{
		m->dump = ft_atoi(av[++(*i)]);
		return (true);
	}
	if (!ft_strcmp(av[*i], "-vis"))
	{
		m->v_flag = true;
		return (true);
	}
	return (false);
}