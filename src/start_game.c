/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:37:15 by lshellie          #+#    #+#             */
/*   Updated: 2020/06/12 14:21:09 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		sort_players(t_main *m)
{
	t_player	*cur;
	int			i;

	i = -1;
	while (++i < 4 && m->player)
	{
		cur = m->player;
		while (cur->next)
		{
			if (cur->num > cur->next->num)
				swap_players(cur, cur->next);
			cur = cur->next;
		}
	}
}

int			paste_code(t_main *main, t_player *player, int pos)
{
	int		i;

	i = -1;
	while (++i < player->size)
	{
		main->field[(pos + i) % MEM_SIZE] = player->code[i];
		main->changes[(pos + i) % MEM_SIZE] = player->num + 10;
	}
	return (1);
}

int			set_players(t_main *main)
{
	int			pos0;
	int			pos;
	t_player	*cur;

	pos = 0;
	cur = main->player;
	pos0 = MEM_SIZE / main->num_of_players;
	while (cur)
	{
		set_cursor(&(main->cursor), new_cursor());
		main->cursor->reg[0] = -(cur->num + 1);
		main->cursor->id = main->cursor_ids++;
		paste_code(main, cur, pos);
		main->cursor->pos = pos;
		// main->cursor->creater_no = cur->num;
		// ft_printf("\n__%i__\n",cur->num);
		pos += pos0;
		cur = cur->next;
	}
	return (1);
}

int			introduce(t_player *player)
{
	t_player *cur;

	cur = player;
	ft_putendl("Introducing contestants...");
	while (cur)
	{
		ft_putstr("* Player ");
		ft_putnbr(cur->num + 1);
		ft_putstr(", weighing ");
		ft_putnbr(cur->size);
		ft_putstr(" bytes, \"");
		ft_putstr(cur->name);
		ft_putstr("\" (\"");
		ft_putstr(cur->comment);
		ft_putendl("\") !");
		cur = cur->next;
	}
	return (1);
}

int			start_game(t_main *main)
{
	if (main->v_flag)
		init_visualisation(main);
	sort_players(main);
	introduce(main->player);
	set_players(main);
	if (!main->v_flag && !(start_fight(main)))
			return (0);
	if (main->v_flag)
		start_fight_mlx_hooks(main);
	return (1);
}