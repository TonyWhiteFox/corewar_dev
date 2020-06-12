/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 17:34:06 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/07 14:58:26 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void			carriage_refresh(t_car *self)
{
	ft_bzero(&self->args, sizeof(self->args));
	ft_bzero(&self->arg_val, sizeof(self->arg_val));
	self->cur_operation = -1;
	self->cycles_to_wait = -1;
}

void				perform_next_comm(t_car *self, t_vm *v)
{
	if ((*self->pc > REG_NUMBER || *self->pc == 0)
	&& (self->cycles_to_wait < 0))
	{
		move_pc(self, v, 1, false);
		return ;
	}
	while (self->cycles_to_wait < 0 && ++self->cur_operation < REG_NUMBER)
		if (g_func_tab[self->cur_operation].opcode == *self->pc)
			self->cycles_to_wait = g_func_tab[self->cur_operation].cycles;
	if (--self->cycles_to_wait == 0)
	{
		if (vnp_codage(self, v) < 0)
		{
			move_pc(self, v, self->pc_padding, false);
			self->pc_padding = 0;
			carriage_refresh(self);
			return ;
		}
		g_func_tab[self->cur_operation].f(self, v);
		carriage_refresh(self);
	}
}

int					find_addr(int res)
{
	res %= MEM_SIZE;
	(res < 0) ? res += MEM_SIZE : 1;
	return (res);
}
