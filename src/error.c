/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:06:17 by lshellie          #+#    #+#             */
/*   Updated: 2020/03/04 10:46:07 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

void	free_cursor(t_main *main)
{
	t_cursor	*tmp;
	t_cursor	*c;

	c = main->cursor;
	while (c)
	{
		tmp = c->next;
		free(c->reg);
		free(c);
		c = tmp;
	}
	main->cursor = 0;
}

void	free_player(t_player *player)
{
	t_player *tmp;

	while (player)
	{
		if (player->name)
			free(player->name);
		if (player->comment)
			free(player->comment);
		if (player->code)
			free(player->code);
		tmp = player;
		player = player->next;
		free(tmp);
	}
}

void	free_main(t_main *main)
{
	free_player(main->player);
	free_cursor(main);
	free(main->field);
	free(main);
}

int		ft_error(char *str)
{
	ft_putendl(str);
	return (0);
}
