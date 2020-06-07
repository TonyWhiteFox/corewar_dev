/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:55:22 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/07 19:01:18 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "corewar.h"

void	init_cl_bufers(t_opencl *o)
{
	o->ret_pic = (cl_int *)malloc(sizeof(cl_int) * o->win_size);
	o->mem_picture = clCreateBuffer(o->context, CL_MEM_WRITE_ONLY, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
	o->mem_field = clCreateBuffer(o->context, CL_MEM_READ_ONLY, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
	o->mem_changers = clCreateBuffer(o->context, CL_MEM_READ_ONLY, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
}

void		init_cl_kernel(t_opencl *o)
{
	int		fd;
	char	*temp1;
	char	*temp2;
	int		j;
	
	fd = open("src/opencl/mandelbrot.cl", O_RDONLY);
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
	o->ret = clGetDeviceIDs(o->platform_id, CL_DEVICE_TYPE_GPU, 1,
				&o->device_id, &o->ret_num_devices);
	o->context = clCreateContext(NULL, 1, &o->device_id, NULL, NULL, &o->ret);
	o->command_queue = clCreateCommandQueue(o->context,
				o->device_id, 0, &o->ret);
	init_cl_kernel(o);
	o->kernel_size = ft_strlen(o->file);
	o->program = clCreateProgramWithSource(o->context, 1,
			(const char **)&o->file, (const size_t *)&o->kernel_size, &o->ret);
	o->ret = clBuildProgram(o->program, 1, &o->device_id, NULL, NULL, NULL);
	o->kernel = clCreateKernel(o->program, "kercorewar", &o->ret);
	o->win_size = m->w_x * m->w_y;
	
}

void	init_mlx(t_mlx *mlx, t_main *m)
{

}

void	init_visualisation(t_main *m)
{
	m->changes = (size_t *)malloc(MEM_SIZE);
	
	m->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	m->opencl = (t_opencl *)malloc(sizeof(t_opencl));
	m->w_x = 1792; //64*28
	m->w_y = 1024; //64*16
}