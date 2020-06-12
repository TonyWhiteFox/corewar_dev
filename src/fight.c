/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:53:05 by lshellie          #+#    #+#             */
/*   Updated: 2020/06/12 12:47:47 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			g_price[17] = {PRICE, 10, 5, 5, 10, 10, 6,
	6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

void		do_or_wait(t_main *main, t_cursor *c)
{
	if (c->action == -1)
	{
		c->pos = c_p(c->pos + 1);
		c->action = 0;
		c->op = 0;
	}
	else
	{
		--c->action;
		if (c->action == 0)
			do_op(main, c);
	}
}

void		read_byte(t_main *main, t_cursor *c)
{
	c->op = main->field[c->pos];
	if (c->op > 0 && c->op <= MAX_OPS)
		c->action = g_price[c->op];
	else
		c->action = -1;
}

void		do_cursor(t_main *main, t_cursor *c)
{
	if (c->action == 0)
		read_byte(main, c);
	do_or_wait(main, c);
}

void		do_cycle(t_main *main)
{
	t_cursor	*cur;

	cur = main->cursor;
	while (cur)
	{
		do_cursor(main, cur);
		cur = cur->next;
	}
}

int			start_fight(t_main *m)
{
	while (m->cursor)
	{
		++m->cycle;
		++m->total_cycle;
		do_cycle(m);
		if (m->cycle == m->cycles_to_die || m->cycles_to_die <= 0)
			check(m);
		if (m->cursor && (m->dump == m->total_cycle || m->dump == 0))
		{
			dump_memory(m->field);
			return (0);
		}
	}
	ft_printf("%i ", m->total_cycle);
	return (1);
}

void		send_memory_buffers_to_cl(t_main *m, t_opencl *o)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		o->send_field[i] = (cl_uchar) m->field[i];
		i++;
	}
	
	// ft_printf("\n%i+++\n", o->win_size * sizeof(cl_int));
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
								o->win_size * sizeof(cl_int),
								o->ret_pic, 0, NULL, NULL);
	// ft_printf("21_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_field, CL_TRUE, 0,
								MEM_SIZE * sizeof(cl_uchar), o->send_field,
								0, NULL, NULL);
	// ft_printf("22_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_changers, CL_TRUE,
								0, MEM_SIZE * sizeof(cl_int), (cl_int *)
								m->changes, 0, NULL, NULL);
	// ft_printf("23_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 0, sizeof(cl_mem),
							(void *)&o->mem_picture);
	// ft_printf("31_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 1, sizeof(cl_mem),
							(void *)&o->mem_field);
	// ft_printf("32_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 2, sizeof(cl_mem),
							(void *)&o->mem_changers);
	// ft_printf("33_%i\n", o->ret);
	// exit(0);
}

void		execute_cl(t_main *m, t_opencl *o, t_mlx *ml)
{
	size_t	i;

	o->ret = clEnqueueNDRangeKernel(o->command_queue, o->kernel, 1, NULL,
									&o->flows, NULL, 0, NULL, NULL);
	// ft_printf("51_%i\n", o->ret);
	o->ret = clEnqueueReadBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
			o->win_size * sizeof(cl_int), o->ret_pic, 0, NULL, NULL);
	// ft_printf("52_%i\n", o->ret);
	i = 0;
	while (i < o->win_size)
	{
		*(int *)(ml->img_adr + i * 4) = o->ret_pic[i];
		i++;
	}
	mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);
	mlx_string_put(ml->mlx_ptr, ml->win_ptr, 1600, 100, 0xFFFFFF, ft_itoa(m->total_cycle));
	// ft_printf()
	// exit(0);
}

void		send_argument_to_cl(t_main *m, t_opencl *o)
{
	cl_int	tmp_int;
	send_memory_buffers_to_cl(m, o);
	tmp_int = (cl_int)m->w_x;
	o->ret = clSetKernelArg(o->kernel, 3, sizeof(cl_int), &tmp_int);
	// ft_printf("41_%i\n", o->ret);
	tmp_int = (cl_int)m->w_y;
	o->ret = clSetKernelArg(o->kernel, 4, sizeof(cl_int), &tmp_int);
	// ft_printf("42_%i\n", o->ret);
	tmp_int = (cl_int)o->flows;
	o->ret = clSetKernelArg(o->kernel, 5, sizeof(cl_int), &tmp_int);
	// ft_printf("43_%i\n", o->ret);
	tmp_int = (cl_int)m->total_cycle;
	o->ret = clSetKernelArg(o->kernel, 6, sizeof(cl_int), &tmp_int);
	execute_cl(m, o, m->mlx);
	// exit(0);
}

int			start_fight_vis(t_main *m)
{
	if (m->cursor)
	{
		++m->cycle;
		++m->total_cycle;
		do_cycle(m);
		if (m->cycle == m->cycles_to_die || m->cycles_to_die <= 0)
			check(m);
		send_argument_to_cl(m, m->opencl);
	}
	else
	{
		send_argument_to_cl(m, m->opencl);
		choose_winner(m);
		exit(0);
		mlx_hook(m->mlx->win_ptr, 2, 2, key_press, m);
		mlx_hook(m->mlx->win_ptr, 17, 17, say_good_buy, m);
		mlx_hook(m->mlx->win_ptr, 4, 4, mouse_click_hook, m);
		mlx_hook(m->mlx->win_ptr, 6, 6, mouse_move_hook, m);
		mlx_loop(m->mlx->mlx_ptr);
	}
	return(0);
}

void		start_fight_mlx_hooks(t_main *m)
{
	mlx_loop_hook(m->mlx->mlx_ptr, start_fight_vis, m);
	mlx_hook(m->mlx->win_ptr, 2, 2, key_press, m);
	mlx_hook(m->mlx->win_ptr, 17, 17, say_good_buy, m);
	mlx_hook(m->mlx->win_ptr, 4, 4, mouse_click_hook, m);
	mlx_hook(m->mlx->win_ptr, 6, 6, mouse_move_hook, m);
	mlx_loop(m->mlx->mlx_ptr);
}
