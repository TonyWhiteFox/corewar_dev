/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_visual_fight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 19:05:18 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/14 21:34:48 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		execute_cl(t_main *m, t_opencl *o, t_mlx *ml)
{
	size_t	i;

	i = o->flows + 320;
	o->ret = clEnqueueNDRangeKernel(o->command_queue, o->kernel, 1, NULL,
									&i, NULL, 0, NULL, NULL);
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
	// mlx_string_put(ml->mlx_ptr, ml->win_ptr, 1600, 100, 0xFFFFFF, ft_itoa(m->total_cycle));
	// if (m->total_cycle % 500 == 0)
	// 	ft_printf("%i\n", m->total_cycle);
	// exit(0);
}

void		send_memory_buffers_to_cl(t_main *m, t_opencl *o)
{
	
	// ft_printf("\n%i+++\n", o->win_size * sizeof(cl_int));
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
								o->win_size * sizeof(cl_int),
								o->ret_pic, 0, NULL, NULL);
	// ft_printf("21_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_field, CL_TRUE, 0,
								MEM_SIZE * sizeof(cl_uchar), m->field,
								0, NULL, NULL);
	// ft_printf("22_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_changers, CL_TRUE,
								0, MEM_SIZE * sizeof(cl_int),
								m->changes, 0, NULL, NULL);
	// ft_printf("23_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_cursor, CL_TRUE,
								0, MEM_SIZE * sizeof(bool),
								m->have_cursor, 0, NULL, NULL);
	// ft_printf("24_%i\n", o->ret);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_live, CL_TRUE,
								0, MEM_SIZE * sizeof(cl_int),
								m->live, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_decor, CL_TRUE,
								0, 285 * sizeof(bool),
								o->decor, 0, NULL, NULL);
	// ft_printf("25_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 0, sizeof(cl_mem),
							(void *)&o->mem_picture);
	// ft_printf("31_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 1, sizeof(cl_mem),
							(void *)&o->mem_field);
	// ft_printf("32_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 2, sizeof(cl_mem),
							(void *)&o->mem_changers);
	// ft_printf("33_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 3, sizeof(cl_mem),
							(void *)&o->mem_cursor);
	// ft_printf("34_%i\n", o->ret);
	o->ret = clSetKernelArg(o->kernel, 4, sizeof(cl_mem),
							(void *)&o->mem_live);
	o->ret = clSetKernelArg(o->kernel, 5, sizeof(cl_mem),
							(void *)&o->mem_decor);
	// ft_printf("35_%i\n", o->ret);
	// exit(0);
}

void		send_argument_to_cl(t_main *m, t_opencl *o)
{
	cl_int	tmp_int;
	send_memory_buffers_to_cl(m, o);
	tmp_int = (cl_int)m->w_x;
	o->ret = clSetKernelArg(o->kernel, 6, sizeof(cl_int), &tmp_int);
	// ft_printf("41_%i\n", o->ret);
	// tmp_int = (cl_int)m->w_y;
	// o->ret = clSetKernelArg(o->kernel, 6, sizeof(cl_int), &tmp_int);
	// // ft_printf("42_%i\n", o->ret);
	
	// ft_printf("43_%i\n", o->ret);
	tmp_int = (cl_int)m->total_cycle;
	o->ret = clSetKernelArg(o->kernel, 7, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)o->flows;
	o->ret = clSetKernelArg(o->kernel, 8, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)m->cycles_to_die;
	o->ret = clSetKernelArg(o->kernel, 9, sizeof(cl_int), &tmp_int);
	execute_cl(m, o, m->mlx);
	// usleep(60000);
	// exit(0);
}

int			start_fight_vis(t_main *m)
{
	if (m->cursor)
	{
		ft_bzero(m->have_cursor, MEM_SIZE * sizeof(bool));
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