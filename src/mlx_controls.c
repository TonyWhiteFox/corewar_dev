/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:17:10 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/07 21:35:41 by ldonnor-         ###   ########.fr       */
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
	return (0);
}