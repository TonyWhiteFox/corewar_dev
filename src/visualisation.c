/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:55:22 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/14 22:15:36 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_cl_bufers(t_opencl *o)
{
	o->ret_pic = (cl_int *)malloc(sizeof(cl_int) * o->win_size);
	// o->send_field = (cl_char *)malloc(sizeof(cl_char) * MEM_SIZE);
	o->mem_picture = clCreateBuffer(o->context, CL_MEM_READ_WRITE, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
	ft_printf("10_%i\n", o->ret);
	o->mem_field = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_char), NULL, &o->ret);
	ft_printf("11_%i\n", o->ret);
	o->mem_changers = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_int), NULL, &o->ret);
	ft_printf("12_%i\n", o->ret);
	o->mem_cursor = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(bool), NULL, &o->ret);
	ft_printf("13_%i\n", o->ret);
	o->mem_live = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_int), NULL, &o->ret);
	ft_printf("14_%i\n", o->ret);
	o->mem_decor = clCreateBuffer(o->context, CL_MEM_READ_ONLY, 285 *
				sizeof(bool) , NULL, &o->ret);
	ft_printf("15_%i\n", o->ret);
}

void		init_cl_kernel(t_opencl *o)
{
	int		fd;
	char	*temp1;
	char	*temp2;
	int		j;
	
	fd = open("src/opencl/paint_map.cl", O_RDONLY);
	// fd = open("src/opencl/mandelbrot.cl", O_RDONLY);
	o->file = ft_strnew(1);
	while ((j = get_next_line(fd, &temp1)))
	{
		temp2 = o->file;
		o->file = ft_strjoin(o->file, temp1);
		free(temp1);
		free(temp2);
	}
	close(fd);
}

void	init_opencl(t_opencl *o, t_main *m)
{
	o->ret = clGetPlatformIDs(1, &o->platform_id, &o->ret_num_platforms);
	ft_printf("1_%i\n", o->ret);
	o->ret = clGetDeviceIDs(o->platform_id, CL_DEVICE_TYPE_GPU, 1,
				&o->device_id, &o->ret_num_devices);
	ft_printf("2_%i\n", o->ret);
	o->context = clCreateContext(NULL, 1, &o->device_id, NULL, NULL, &o->ret);
	ft_printf("3_%i\n", o->ret);
	o->command_queue = clCreateCommandQueue(o->context,
				o->device_id, 0, &o->ret);
	ft_printf("4_%i\n", o->ret);			
	init_cl_kernel(o);
	ft_printf("4_2_%i\n", o->ret);
	o->kernel_size = ft_strlen(o->file);
	o->program = clCreateProgramWithSource(o->context, 1,
			(const char **)&o->file, (const size_t *)&o->kernel_size, &o->ret);
	ft_printf("5_%i\n", o->ret);		
	o->ret = clBuildProgram(o->program, 1, &o->device_id, NULL, NULL, NULL);
	ft_printf("6_%i\n", o->ret);
	o->kernel = clCreateKernel(o->program, "kercorewar", &o->ret);
	// o->kernel = clCreateKernel(o->program, "kerjulia", &o->ret);
	ft_printf("7_%i\n", o->ret);
	o->win_size = m->w_x * m->w_y;
	init_cl_bufers(o);
}

void	init_mlx(t_mlx *mlx, t_main *m)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, m->w_x, m->w_y, "corewar");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, m->w_x, m->w_y);
	mlx->img_adr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
					&mlx->stride, &mlx->endian);
	mlx->bpp /= 8;
	mlx->cycle_per_frame = 1;
	mlx->sleep_after_frame = 0;
	mlx->stop = false;
}

void	init_visualisation(t_main *m)
{
	m->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	m->opencl = (t_opencl *)malloc(sizeof(t_opencl));
	m->w_x = 1792; //64*28
	m->w_y = 1024; //64*16
	m->opencl->decor = (bool *)malloc(sizeof(bool) * 285);
	ft_bzero(m->opencl->decor, sizeof(bool) * 285);
	fill_decor_bool_array(m->opencl);
	m->opencl->flows = MEM_SIZE * 2;
	init_opencl(m->opencl, m);
	init_mlx(m->mlx, m);
}