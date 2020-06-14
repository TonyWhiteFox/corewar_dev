/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:17:10 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/14 22:57:09 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		mouse_move_hook(int x, int y, t_main *m)
{
	return (0);
}

int		mouse_click_hook(int k, int x, int y, t_main *m)
{
	return (0);
}

int		say_good_buy(t_main *m)
{
	exit(0);
	free(m);
	return (0);
}

int		key_press(int key, t_main *m)
{
	if (key == 53)
		say_good_buy(m);
	if (key == 24 && m->mlx->cycle_per_frame < 99)
		if (m->mlx->sleep_after_frame == 0)
			m->mlx->cycle_per_frame += 1;
		else
			m->mlx->sleep_after_frame -= 1000;
	if (key == 27)
		if (m->mlx->cycle_per_frame > 1)
			m->mlx->cycle_per_frame -= 1;
		else
			m->mlx->sleep_after_frame += 1000;
		
	ft_printf("%i\n", key);
	return (0);
}