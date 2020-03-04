/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cursors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:07:16 by lshellie          #+#    #+#             */
/*   Updated: 2020/03/04 12:52:39 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_cursors_while(t_main *m, t_cursor *c, t_cursor *prev)
{
	while (c)
	{
		if (m->total_cycle - c->last_live_cycle >= m->cycles_to_die)
		{
			if (!prev)
			{
				m->cursor = c->next;
				free(c->reg);
				free(c);
				c = m->cursor;
				continue ;
			}
			else
			{
				prev->next = c->next;
				free(c->reg);
				free(c);
				c = prev;
			}
		}
		prev = c;
		c = c->next;
	}
}

int		check_cursors(t_main *m)
{
	t_cursor	*c;
	t_cursor	*prev;

	prev = 0;
	c = m->cursor;
	if (m->cycles_to_die <= 0)
	{
		free_cursor(m);
		return (1);
	}
	check_cursors_while(m, c, prev);
	return (1);
}

int		check(t_main *main)
{
	++main->check_num;
	check_cursors(main);
	if (main->live_num >= NBR_LIVE)
	{
		main->cycles_to_die -= CYCLE_DELTA;
		main->check_num = 0;
	}
	else if (main->check_num >= MAX_CHECKS)
	{
		main->cycles_to_die -= CYCLE_DELTA;
		main->check_num = 0;
	}
	main->live_num = 0;
	main->cycle = 0;
	return (1);
}
