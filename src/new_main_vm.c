/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:04:13 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/20 21:41:53 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		close_fd_send_error_close(t_virt *v, char *error_text)
{
	close(v->fd);
	exit(ft_printf("%s\n", error_text));
}

void		check_format(char *av, int i)
{
	if (i > 4)
		if (ft_strequ(&(av[i - 4]), ".cor"))
			return ;
	exit(ft_printf("Invalid file format\n")); 
}

void		init_start_params2(t_virt *v)
{
	v->life_in_die_cycle = 0;
}
void		init_start_params(t_virt *v)
{
	v->d = -1;
	v->dump = -1;
	v->vis = false;
	v->total_gamers = 0;
	v->gamer = NULL;
	v->serf = NULL;
	v->map = (cl_uchar *)malloc(sizeof(cl_uchar) * MEM_SIZE);
	ft_bzero(v->map, sizeof(cl_uchar) * MEM_SIZE);
	v->log = (cl_uint *)malloc(sizeof(cl_uint) * MEM_SIZE);
	ft_bzero(v->log, sizeof(cl_uint) * MEM_SIZE);
	v->last_serf_id = 0;
	v->total_cycles = 0;
	v->cycles = 0;
	v->option = (t_option *)malloc(sizeof(t_option));
	ft_bzero(v->option, sizeof(t_option));
	v->option->var_type = (int *)malloc(sizeof(int) * 3);
	v->option->var_len = (int *)malloc(sizeof(int) * 3);
	v->option->variable = (int *)malloc(sizeof(int) * 3);
	init_start_params2(v);
}

int			find_vis_or_dumps(int ac, char **av, t_virt *v, int i)
{
	if (ft_strequ(av[i], "-vis"))
	{
		if (v->vis)
			exit(ft_printf("Bag arguments!\nRun ./corewar for help\n"));
		v->vis = true;
		return (1);
	}
	if (((ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-d")) && ((v->dump
		+ v->d) == -2)) && (i + 1 < ac) && ft_is_positive_number(av[i + 1]))
	{
		if (ft_strequ(av[i], "-dump"))
			v->dump = ft_atoi(av[i + 1]);
		else
			v->d = ft_atoi(av[i + 1]);
		if (v->d + v->dump > -2)
			return(2);
	}
	return(0);
}

void		skip_empty(t_virt *v, int i, char tmp_ch)
{
	while (i > 0)
	{
		if (read(v->fd, &(tmp_ch), 1) < 0)
			close_fd_send_error_close(v, "Error reading file!");
		if (tmp_ch != 0)
			close_fd_send_error_close(v, "Haven't NULL byte!");
		i--;
	}
}

void		read_name(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->name = (char *)malloc(129);
	ft_bzero(new_gamer->name, 129);
	if ((read(v->fd, new_gamer->name, 128)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
}

void		read_comment(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->comment = (char *)malloc(2049);
	ft_bzero(new_gamer->comment, 2049);
	if ((read(v->fd, new_gamer->comment, 2048)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
}

void		read_body(t_virt *v, t_gamer *new_gamer, int readed_byte, char test_for_read)
{
	new_gamer->code = (char *)malloc(new_gamer->size + 1);
	ft_bzero(new_gamer->code, new_gamer->size + 1);
	if ((readed_byte = read(v->fd, new_gamer->code, new_gamer->size)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
	if ((readed_byte != new_gamer->size) ||
			((read(v->fd, &test_for_read, 1)) > 0))
		close_fd_send_error_close(v, "Champion's size in file is false");
}

int			get_int_in_fd(t_virt *v, int i, int tmp_int, unsigned char tmp_ch)
{
	while (i < 4)
	{
		if (read(v->fd, &(tmp_ch), 1) != 1)
			close_fd_send_error_close(v, "Error reading file!");
		tmp_int += tmp_ch << (8 * (3 - i));
		i++;
	}
	return (tmp_int);
}

void		read_size(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->size = get_int_in_fd(v, 0, 0, 0);
	if (new_gamer->size < 0 || new_gamer->size > CHAMP_MAX_SIZE)
		close_fd_send_error_close(v, "Invalid champion's size!");
}

void		create_gamer_and_fill_him(t_virt *v, t_gamer *new_gamer,
										t_gamer *temp_gamer)
{
	new_gamer = (t_gamer *)malloc(sizeof(t_gamer));
	new_gamer->num = v->number;
	new_gamer->next = NULL;
	temp_gamer = v->gamer;
	if (!(v->gamer))
		v->gamer = new_gamer;
	else
	{	
		while (temp_gamer->next)
			temp_gamer = temp_gamer->next;
		temp_gamer->next = new_gamer;
	}
	if (get_int_in_fd(v, 0, 0, 0) != COREWAR_EXEC_MAGIC)
		close_fd_send_error_close(v, "Header error COREWAR_EXEC_MAGIC");
	read_name(v, new_gamer);
	skip_empty(v, 4, 0);
	read_size(v, new_gamer);
	read_comment(v, new_gamer);
	skip_empty(v, 4, 0);
	read_body(v, new_gamer, 0, 0);
}

void		read_gamers(char *av, t_virt *v)
{
	if (v->total_gamers >= MAX_PLAYERS)
		exit(ft_printf("Exceeded the player limit\n"));
	v->total_gamers++;
	v->fd = open(av, O_RDONLY);
	if (v->fd < 1)
		exit(ft_printf("Unreadable file!\n"));
	if (v->number == 0)
		v->number = v->total_gamers * (-1);
	create_gamer_and_fill_him(v, NULL, NULL);
	close(v->fd);
}

int			find_player(int ac, char **av, t_virt *v, int i)
{
	if (ft_strequ(av[i], "-n") && i + 2 < ac &&
			ft_is_positive_number(av[i + 1]))
	{
		v->number = ft_atoi(av[i + 1]);
		if (v->number < 1 || v->number > MAX_PLAYERS)
			return (0);
		check_format(av[i + 2], ft_strlen(av[i + 2]));
		read_gamers(av[i + 2], v);
		return(3);
	}
	v->number = 0;
	check_format(av[i], ft_strlen(av[i]));
	read_gamers(av[i], v);
	return(1);
}

void		check_program_args(int ac, char **av, t_virt *v, int i)
{
	if (ac < 2)
	{
		ft_printf("Use: ./corewar with arguments: {-vis or -dump (int) ");
		ft_printf("or -d (int)} {-n (int)} (Player_name).cor\n");
		ft_printf("\t-vis run visualization\n\t-d (int) or -dump (int) ");
		ft_printf("stop corwar after (int) cycles and print map\n\t-n");
		ft_printf(" (int) change start name for next player\n");
		exit(0);
	}
	init_start_params(v);
	while (i < ac)
	{
		v->temp = i;
		i += find_vis_or_dumps(ac, av, v, i);
		if (v->temp == i)
		{
			i += find_player(ac, av, v, i);
			if (v->temp == i)
				exit(ft_printf("Bag arguments!\nRun ./corewar for help\n"));
		}
	}
}

t_gamer		*gamer_swap(t_gamer *swap_now, t_gamer *swap_next, t_gamer *swap_prew,
						t_virt *v)
{
	if (swap_now == v->gamer)
		v->gamer = swap_next;
	else
		swap_prew->next = swap_next;
	swap_now->next = swap_next->next;
	swap_next->next = swap_now;
	return(swap_next);
}

void		gamer_buble_sorting(t_virt *v, t_gamer *first_cycle,
							t_gamer *second_cycle, t_gamer *temp)
{
	while (first_cycle->next)
	{
		second_cycle = v->gamer;
		while (second_cycle->next)
		{
			if (second_cycle->next->num > v->total_gamers ||
					second_cycle->num > v->total_gamers)
				exit(ft_printf("Maximal player num = sum players!\n"));
			if (second_cycle->num == second_cycle->next->num)
				exit(ft_printf("Duplicate player num!\n"));
			if (second_cycle->num > second_cycle->next->num)
			{
				second_cycle = gamer_swap(second_cycle,
							second_cycle->next, temp, v);
				first_cycle = v->gamer;
			}
			temp = second_cycle;
			second_cycle = second_cycle->next;
		}
		first_cycle = first_cycle->next;
	}
}

void		get_all_number_for_gamers(t_gamer *gamer)
{
	while (gamer->next)
	{
		gamer->num *= -1;
		gamer = gamer->next;
	}
}

int			find_empty_num(t_virt *v, t_gamer *gamer, int numb, int temp)
{
	while (numb <= v->total_gamers)
	{
		while (gamer)
		{
			if (numb < gamer->num)
				return(numb);
			if (numb == gamer->num)
			{
				numb++;
				temp = gamer->num;
				gamer = gamer->next;
			}
		}
		if (numb < temp)
			return (numb);
		else
			numb++;
	}
	return (0);
}

void		find_last_negative_player(t_virt *v, t_gamer *gamer,
								t_gamer *temp, bool isFind)
{
	while (gamer->next && !isFind)
		if (gamer->next->num > 0)
			isFind = TRUE;
		else
			gamer = gamer->next;
	if (!isFind)
		get_all_number_for_gamers(v->gamer);
	else
	{
		temp = gamer->next;
		gamer->num = find_empty_num(v, temp, 1, 0);
	}
}

void		gamer_on_show(t_gamer *gamer)
{
	ft_printf("Introducing contestants...\n");
	while (gamer)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
				gamer->num, gamer->size, gamer->name, gamer->comment);
		gamer = gamer->next;
	}
}

void		create_serf(t_virt *v, t_serf *surf)
{
	surf = (t_serf *)malloc(sizeof(t_serf));
	ft_bzero(surf, sizeof(t_serf));
	surf->next = NULL;
	surf->reg = (int *)malloc(sizeof(int) * REG_NUMBER);
	ft_bzero(surf->reg, sizeof(sizeof(int) * REG_NUMBER));

	if (!v->serf)
		v->serf = surf;
	else
	{
		surf->next = v->serf;
		v->serf = surf;
	}
}

void		get_start_pos_and_first_serf(t_virt *v, t_gamer *gamer,
										int start_pos, int i)
{
	while (gamer)
	{
		create_serf(v, NULL);
		i = 0;
		while (i < gamer->size)
		{
			v->map[(start_pos + i) % MEM_SIZE] = gamer->code[i];
			v->log[(start_pos + i) % MEM_SIZE] = gamer->num;
			i++;
		}
		v->serf->reg[0] = gamer->num * (-1);
		v->serf->creater_no = gamer->num;
		v->last_serf_id += 1;
		v->serf->id = v->last_serf_id;
		v->serf->pos = start_pos;
		start_pos += MEM_SIZE / v->total_gamers;
		gamer = gamer->next;
	}
}

void		send_gamers(t_virt *v)
{
	if (v->total_gamers == 0)
		exit(ft_printf("No gamers!\nRun ./corewar for help\n"));
	if (v->gamer->num > v->total_gamers)
				exit(ft_printf("Maximal player num = sum players!\n"));
	gamer_buble_sorting(v, v->gamer, v->gamer, v->gamer);
	while (v->gamer->num < 0)
	{
		find_last_negative_player(v, v->gamer, NULL, FALSE);
		gamer_buble_sorting(v, v->gamer, v->gamer, v->gamer);
	}
	gamer_on_show(v->gamer);
	get_start_pos_and_first_serf(v, v->gamer, 0, 0);
}

void		fill_decor_array4(t_opencl *o)
{
	o->decor[221] = true;
	o->decor[226] = true;
	o->decor[228] = true;
	o->decor[230] = true;
	o->decor[232] = true;
	o->decor[234] = true;
	o->decor[236] = true;
	o->decor[241] = true;
	o->decor[243] = true;
	o->decor[245] = true;
	o->decor[247] = true;
	o->decor[249] = true;
	o->decor[251] = true;
	o->decor[257] = true;
	o->decor[259] = true;
}

void		fill_decor_array3(t_opencl *o)
{
	o->decor[139] = true;
	o->decor[140] = true;
	o->decor[166] = true;
	o->decor[170] = true;
	o->decor[181] = true;
	o->decor[185] = true;
	o->decor[187] = true;
	o->decor[188] = true;
	o->decor[189] = true;
	o->decor[191] = true;
	o->decor[192] = true;
	o->decor[193] = true;
	o->decor[196] = true;
	o->decor[200] = true;
	o->decor[202] = true;
	o->decor[204] = true;
	o->decor[206] = true;
	o->decor[211] = true;
	o->decor[213] = true;
	o->decor[215] = true;
	o->decor[217] = true;
	o->decor[218] = true;
	o->decor[219] = true;
	fill_decor_array4(o);
}

void		fill_decor_array2(t_opencl *o)
{
	o->decor[78] = true;
	o->decor[80] = true;
	o->decor[82] = true;
	o->decor[86] = true;
	o->decor[87] = true;
	o->decor[88] = true;
	o->decor[91] = true;
	o->decor[93] = true;
	o->decor[95] = true;
	o->decor[97] = true;
	o->decor[101] = true;
	o->decor[106] = true;
	o->decor[108] = true;
	o->decor[109] = true;
	o->decor[110] = true;
	o->decor[112] = true;
	o->decor[116] = true;
	o->decor[117] = true;
	o->decor[118] = true;
	o->decor[121] = true;
	o->decor[136] = true;
	o->decor[137] = true;
	o->decor[138] = true;
	fill_decor_array3(o);
}

void		fill_decor_array(t_opencl *o)
{
	o->decor[16] = true;
	o->decor[17] = true;
	o->decor[18] = true;
	o->decor[19] = true;
	o->decor[20] = true;
	o->decor[31] = true;
	o->decor[46] = true;
	o->decor[48] = true;
	o->decor[49] = true;
	o->decor[50] = true;
	o->decor[52] = true;
	o->decor[53] = true;
	o->decor[54] = true;
	o->decor[56] = true;
	o->decor[57] = true;
	o->decor[58] = true;
	o->decor[61] = true;
	o->decor[63] = true;
	o->decor[65] = true;
	o->decor[67] = true;
	o->decor[71] = true;
	o->decor[73] = true;
	o->decor[76] = true;
	fill_decor_array2(o);
}


void		heat_cl_bufers(t_opencl *o)
{
	o->ret_pic = (cl_int *)malloc(sizeof(cl_int) * o->win_size);
	o->mem_picture = clCreateBuffer(o->context, CL_MEM_READ_WRITE, o->win_size *
				sizeof(cl_int), NULL, &o->ret);
	o->mem_map = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_uchar), NULL, &o->ret);
	o->mem_log = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_uint), NULL, &o->ret);
	o->mem_serf = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(bool), NULL, &o->ret);
	o->mem_live = clCreateBuffer(o->context, CL_MEM_READ_ONLY, MEM_SIZE *
				sizeof(cl_uint), NULL, &o->ret);
	o->mem_decor = clCreateBuffer(o->context, CL_MEM_READ_ONLY, 285 *
				sizeof(bool) , NULL, &o->ret);
}

void		heat_cl_kernel(t_opencl *o)
{
	int		fd;
	char	*temp1;
	char	*temp2;
	int		j;
	
	fd = open("src/opencl/paint_map.cl", O_RDONLY);
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

void		heat_opencl(t_opencl *o, t_virt *v)
{
	o->ret = clGetPlatformIDs(1, &o->platform_id, &o->ret_num_platforms);
	o->ret = clGetDeviceIDs(o->platform_id, CL_DEVICE_TYPE_GPU, 1,
				&o->device_id, &o->ret_num_devices);
	o->context = clCreateContext(NULL, 1, &o->device_id, NULL, NULL, &o->ret);
	o->command_queue = clCreateCommandQueue(o->context,
				o->device_id, 0, &o->ret);		
	heat_cl_kernel(o);
	o->kernel_size = ft_strlen(o->file);
	o->program = clCreateProgramWithSource(o->context, 1,
			(const char **)&o->file, (const size_t *)&o->kernel_size, &o->ret);
	o->ret = clBuildProgram(o->program, 1, &o->device_id, NULL, NULL, NULL);
	o->kernel = clCreateKernel(o->program, "kercorewar", &o->ret);
	o->win_size = v->w_x * v->w_y;
	heat_cl_bufers(o);
}

void		heat_mlx(t_mlx *mlx, t_virt *v)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, v->w_x, v->w_y, "CoreWar");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, v->w_x, v->w_y);
	mlx->img_adr = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
					&mlx->stride, &mlx->endian);
	mlx->bpp /= 8;
	mlx->cycle_per_frame = 1;
	mlx->sleep_after_frame = 0;
	mlx->stop = false;
}

void		heat_visual(t_virt *v)
{
	v->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	v->opencl = (t_opencl *)malloc(sizeof(t_opencl));
	v->w_x = 1792; //64*28
	v->w_y = 1024; //64*16
	v->opencl->decor = (bool *)malloc(sizeof(bool) * 285);
	ft_bzero(v->opencl->decor, sizeof(bool) * 285);
	fill_decor_array(v->opencl);
	v->opencl->flows = MEM_SIZE * 2;
	heat_opencl(v->opencl, v);
	heat_mlx(v->mlx, v);
}

int			calс_new_pos(int pos)
{
	if (pos >= MEM_SIZE)
		return(pos % MEM_SIZE);
	while (pos < 0)
		pos += MEM_SIZE;
	return(pos); 
}

int				g_live[6] = {1, 0, T_DIR, 0, 0, 4};
int				g_fork[6] = {1, 0, T_DIR, 0, 0, 2};

int			find_num(t_virt *v, t_serf *serf, int pos, int size)
{
	char	dir[4];
	int		i;

	i = 0;
	while (i < size)
	{
		dir[size - i - 1] = v->map[calс_new_pos(serf->pos + pos + i)];
		i++;
	}
	if (size == 4)
		return (*((int *)dir));
	if (size == 2)
		return (*((short *)dir));
	if (size == 1)
		return (dir[0]);
	return (0);
}

void			make_live(t_virt *v, t_serf *serf, int i, int t_dir)
{
	char		dir[4];

	while (i < g_live[T_DIR_SIZE])
	{
		dir[3 - i] = v->map[calс_new_pos(serf->pos + 1 + i)];
		i++;
	}
	t_dir = *((int *)dir);
	v->life_in_die_cycle++;
	serf->last_live_cycle = v->total_cycles;
	if (t_dir < 0 && (ft_abs(t_dir) <= v->total_gamers)) 
	{
		v->player_num_last_say_life = ft_abs(t_dir);
		v->live_log[serf->pos] = v->total_cycles * 10 + v->player_num_last_say_life;
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + g_live[T_DIR_SIZE] + 1);
}

void			make_zjmp(t_virt *v, t_serf *serf, int t_dir)
{
	t_dir = find_num(v, serf, 1, 2);
	if (serf->jump)
		serf->pos = calс_new_pos(serf->pos + t_dir % IDX_MOD);
	else
		serf->pos = calс_new_pos(serf->pos + 3);
	serf->spell = 0;
}

void			make_fork(t_virt *v, t_serf *serf, int i, int dir)
{
	dir = find_num(v, serf, 1, 2);
	if (serf->spell == FORK)
		dir %= IDX_MOD;
	create_serf(v, NULL);
	v->serf->pos = calс_new_pos(serf->pos + dir);
	v->serf->last_live_cycle = serf->last_live_cycle;
	while (i < 16)
	{
		v->serf->reg[i] = serf->reg[i];
		i++;
	}
	v->last_serf_id++;
	v->serf->id = v->last_serf_id;
	v->serf->jump = serf->jump;
	v->serf->creater_no = serf->creater_no;
	serf->pos = calс_new_pos(serf->pos + 3);
	serf->spell = 0;
}


int			g_dir[17] = {T_DIR_SIZE,
	4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};

int			spell_dir_size(int type, int spell)
{
	if (type == REG)
		return (1);
	if (type == IND)
		return (2);
	if (type == DIR)
		return (g_dir[spell]);
	return (0);
}

int			g_num[17] = {NUM_ARG, 1, 2, 2,
	3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

void		calc_option_len(t_serf *serf, t_option *option, int i)
{
	while (i < 3)
	{
		option->var_len[i] = spell_dir_size(option->var_type[i], serf->spell);
		i++;
	}
	i = 0;
	while (i < g_num[serf->spell])
	{
		option->total_len += spell_dir_size(option->var_type[i], serf->spell);
		i++;
	}
}

void		fill_vars(t_virt *v, t_serf *serf, t_option *o, int i)
{
	if (o->var_type[0])
		o->variable[0] = find_num(v, serf, 2, o->var_len[0]);
	if (o->var_type[1])
		o->variable[1] = find_num(v, serf, 2 + o->var_len[0], o->var_len[1]);
	if (o->var_type[2])
		o->variable[2] = find_num(v, serf, 2 + o->var_len[0] + o->var_len[1], o->var_len[2]);
	while (serf->spell != ST && i < 3)
	{
		if (o->var_type[i] == IND)
		{
			if (serf->spell == LLD)
				o->variable[i] = find_num(v, serf, o->variable[i], LLD_READ_SIZE);
			else
				o->variable[i] = find_num(v, serf, o->variable[i] % IDX_MOD, 4);
		}
		i++;
	}
}

bool		check_valid_reg(t_serf *serf, t_option *option, int i)
{
	while (i < g_num[serf->spell])
	{
		if (option->var_type[i] == REG)
		{
			option->variable[i]--;
			if (option->variable[i] < 0 || option->variable[i] > 15)
				return (false);
		}
		i++;
	}
	return (true);
}

bool		check_var_types(t_serf *serf, t_option *option)
{
	if (g_num[serf->spell] == 1 && !option->var_type[0])
		return (false);
	if (g_num[serf->spell] == 2 && (!option->var_type[0] || !option->var_type[1]))
		return (false);
	if (g_num[serf->spell] == 3 && (!option->var_type[0] || !option->var_type[1]
			|| !option->var_type[2]))
		return (false);
	return (true);
}

bool		clean_fill_check_option(t_virt *v, t_serf *serf, unsigned char temp_ch)
{
	ft_bzero(v->option->var_type, sizeof(int) * 3);
	ft_bzero(v->option->var_len, sizeof(int) * 3);
	ft_bzero(v->option->variable, sizeof(int) * 3);
	v->option->total_len = 2;
	temp_ch = v->map[calс_new_pos(serf->pos + 1)];
	v->option->var_type[0] = (temp_ch >> 7) + ((temp_ch << 1) >> 6);
	v->option->var_type[1] = ((temp_ch << 2) >> 7) + ((temp_ch << 3) >> 6);
	v->option->var_type[2] = ((temp_ch << 4) >> 7) + ((temp_ch << 5) >> 6);
	calc_option_len(serf, v->option, 0);
	fill_vars(v, serf, v->option, 0);
	if (!(check_valid_reg(serf, v->option, 0)) || !check_var_types(serf, v->option))
	{
		serf->pos = calс_new_pos(serf->pos + v->option->total_len);
		return (false);
	}
	return (true);
}

// void		do_ld(t_serf *serf, t_option *option)
// {
// 	if ((option->var_type[0] == DIR || option->var_type[0] == IND)
// 		&& option->var_type[1] == REG)
// 	{
// 		c->reg[o->x[1]] = o->x[0];
// 		modify_carry(c, c->reg[o->x[1]]);
// 	}
// 	c->op = 0;
// 	c->pos = c_p(c->pos + o->step);
// }

void		spell_book_with_vars(t_virt *v, t_serf *serf, t_option *option)
{
	// if (serf->spell == LD || serf->spell == LLD)
	// 	make_ld(serf, option);
	// else if (serf->spell == ADD || serf->spell == SUB)
	// 	make_add_sub(v, serf, option);
	// else if (serf->spell == AND || serf->spell == OR || serf->spell == XOR)
	// 	make_and_or_xor(v, serf, option);
	// else if (serf->spell == ST)
	// 	make_st(v, serf, option);
	// else if (serf->spell == STI)
	// 	make_sti(v, serf, option);
	// else if (serf->spell == AFF)
	// 	make_aff(v, serf, option);
	// else if (serf->spell == LDI || serf->spell == LLDI)
	// 	make_ldi(v, serf, option);
}

void		spell_book(t_virt *v, t_serf *serf)
{
	if (serf->spell == LIVE)
		make_live(v, serf, 0, 0);
	else if (serf->spell == ZJMP)
		make_zjmp(v, serf, 0);
	else if (serf->spell == FORK || serf->spell == LFORK)
		make_fork(v, serf, 0, 0);
	else if (clean_fill_check_option(v, serf, 0))
		spell_book_with_vars(v, serf, v->option);
}

int			g_price[17] = {PRICE, 10, 5, 5, 10, 10, 6,
	6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

void		multi_cust(t_virt *v, t_serf *serf)
{
		
	serf->left_to_cust--;
	if (serf->left_to_cust == 0)
		spell_book(v, serf);
	if (serf->left_to_cust < -1)
	{
		serf->pos = calс_new_pos(serf->pos + 1);
		serf->left_to_cust = 0;
		serf->spell = 0;
	}
}

void		make_a_move(t_virt *v, t_serf *serf)
{
	while (serf)
	{
		if (serf->left_to_cust == 0)
		{
			serf->spell = v->map[serf->pos];
			if (serf->spell > 0 && serf->spell <= MAX_OPS)
				serf->left_to_cust = g_price[serf->spell];
			else
				serf->left_to_cust = -1;
		}
		multi_cust(v, serf);
		v->have_serf[serf->pos] = TRUE;
		serf = serf->next;
	}
}

void		hide_show_run(t_virt *v)
{
	while (v->serf)
	{
		v->total_cycles++;
		v->cycles++;
		make_a_move(v, v->serf);
	}
}

void		let_the_show_begin(t_virt *v)
{

}

void		only_one_will_be_left_alive(t_virt *v)
{
	if (v->vis)
		let_the_show_begin(v);
	else
		hide_show_run(v);	
}

/**/
int			main(int ac, char **av)
{
	t_virt	*v;

	if (!(v = (t_virt *)malloc(sizeof(t_virt))))
	{
		ft_putendl("Memory not available!!");
		exit(0);
	}
	check_program_args(ac, av, v, 1);
	send_gamers(v);
	if (v->vis)
		heat_visual(v);
	only_one_will_be_left_alive(v);
}/**/