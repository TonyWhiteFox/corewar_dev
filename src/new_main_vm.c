/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:04:13 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/04 09:49:24 by ldonnor-         ###   ########.fr       */
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
	v->cycles_before_die = CYCLE_TO_DIE;
	v->without_abbreviations = 0;
	v->hardcore = false;
	v->have_serf = (bool *)malloc(sizeof(bool) * MEM_SIZE);
	ft_bzero(v->have_serf, sizeof(bool) * MEM_SIZE);
	v->live_log  = (cl_int *)malloc(sizeof(cl_int) * MEM_SIZE);
	ft_bzero(v->live_log, sizeof(cl_int) * MEM_SIZE);
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
			if (!gamer && numb <= v->total_gamers)
				return(numb);
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
	{
		if (gamer->next->num > 0)
			isFind = TRUE;
		else
			gamer = gamer->next;
	}
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
	int		i;

	i = 0;
	surf = (t_serf *)malloc(sizeof(t_serf));
	ft_bzero(surf, sizeof(t_serf));
	surf->next = NULL;
	surf->reg = (int *)malloc(sizeof(int) * REG_NUMBER);
	while (i < 16)
	{
		surf->reg[i] = 0;
		i++;
	}
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
		v->serf->reg[0] = -(gamer->num);
		v->serf->creater_no = gamer->num;
		v->serf->id = v->last_serf_id;
		v->last_serf_id += 1;
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
		ft_printf("3");
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

void		set_jump(t_serf *serf, int reg)
{
	if (reg != 0)
		serf->jump = 0;
	else
		serf->jump = 1;
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
	//ft_printf("live\n");
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
	//ft_printf("zjmp\n");
	t_dir = find_num(v, serf, 1, 2);
	if (serf->jump)
		serf->pos = calс_new_pos(serf->pos + t_dir % IDX_MOD);
	else
		serf->pos = calс_new_pos(serf->pos + 3);
	serf->spell = 0;
}

void			make_fork(t_virt *v, t_serf *serf, int i, int dir)
{
	//ft_printf("fork\n");
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
	v->option->var_type[0] = (temp_ch / 128) + ((temp_ch % 128) / 64) * 2;
	v->option->var_type[1] = (temp_ch % 64) / 32 + ((temp_ch % 32) / 16) * 2;
	v->option->var_type[2] = (temp_ch % 16) / 8 + ((temp_ch % 8) / 4) * 2;
	//ft_printf("__%i %i %i %i\n", v->map[calс_new_pos(serf->pos + 1)], v->option->var_type[0], v->option->var_type[1], v->option->var_type[2]);
	calc_option_len(serf, v->option, 0);
	//ft_printf("2__%i %i %i %i\n", v->option->total_len, v->option->var_len[0], v->option->var_len[1], v->option->var_len[2]);
	fill_vars(v, serf, v->option, 0);
	//ft_printf("3__%i %i %i\n", v->option->variable[0], v->option->variable[1], v->option->variable[2]);
	if (!(check_valid_reg(serf, v->option, 0) && check_var_types(serf, v->option)))
	{
		//ft_printf("exit_check");
		serf->pos = calс_new_pos(serf->pos + v->option->total_len);
		return (false);
	}
	return (true);
}

void		make_ld(t_serf *serf, t_option *option)
{
	//ft_printf("ld\n");
	if ((option->var_type[0] == DIR || option->var_type[0] == IND)
		&& option->var_type[1] == REG)
	{
		serf->reg[option->variable[1]] = option->variable[0];
		set_jump(serf, serf->reg[option->variable[1]]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		write_reg(t_serf *serf, t_option *option, int i)
{
	while (i < 3)
	{
		if (option->var_type[i] == REG)
			option->variable[i] = serf->reg[option->variable[i]];
		i++;
	}
	//ft_printf("Reg: %i %i %i \n", option->variable[0], option->variable[1], option->variable[2]);
}

void		make_add_sub(t_serf *serf, t_option *option)
{
	//ft_printf("add_sub\n");
	if (option->var_type[0] == REG && option->var_type[1] == REG &&
		option->var_type[2] == REG)
	{
		if (serf->spell == ADD)
			serf->reg[option->variable[2]] = serf->reg[option->variable[1]]
				+ serf->reg[option->variable[0]];
		else if (serf->spell == SUB)
			serf->reg[option->variable[2]] = serf->reg[option->variable[0]]
				- serf->reg[option->variable[1]];
		set_jump(serf, serf->reg[option->variable[2]]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_and_or_xor(t_serf *serf, t_option *option, int save_var)
{
	//ft_printf("and_or_xor\n");
	save_var = option->variable[2];
	write_reg(serf, option, 0);
	if (option->var_type[2] == REG)
	{
		if (serf->spell == AND)
			serf->reg[save_var] = option->variable[0] & option->variable[1];
		else if (serf->spell == OR)
			serf->reg[save_var] = option->variable[0] | option->variable[1];
		else if (serf->spell == XOR)
			serf->reg[save_var] = option->variable[0] ^ option->variable[1];
		set_jump(serf, serf->reg[save_var]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		change_map(t_virt *v, t_serf *serf, int reg, int copy_in_pos)
{
	int		i;
	char	*temp_ch;

	temp_ch = (char *)(&reg);
	//ft_printf("Reg__%i Char__%i %i %i %i\n", reg, temp_ch[0], temp_ch[1], temp_ch[2], temp_ch[3]);
	i = 0;

	while (i < 4)
	{
		v->map[calс_new_pos(copy_in_pos + i)] = temp_ch[3 - i];
		v->log[calс_new_pos(copy_in_pos + i)] = serf->creater_no + v->total_cycles * 10;
		i++;
	}
}

void		make_sti(t_virt *v, t_serf *serf, t_option *option, int save_var)
{
	//ft_printf("sti\n");
	save_var = option->variable[0];
	write_reg(serf, option, 0);
	if ((option->var_type[2] == REG || option->var_type[2] == DIR)
			&& option->var_type[0] == REG)
		change_map(v, serf, serf->reg[save_var], serf->pos
				+ (option->variable[1] + option->variable[2]) % IDX_MOD);
	serf->spell = 0;
	//ft_printf("%i %i\n", serf->pos + option->total_len, option->total_len);
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_st(t_virt *v, t_serf *serf, t_option *option)
{
	//ft_printf("st\n");
	if (option->var_type[0] == REG && option->var_type[1] == REG)
		serf->reg[option->variable[1]] = serf->reg[option->variable[0]];
	if (option->var_type[0] == REG && option->var_type[1] == IND)
		change_map(v, serf, serf->reg[option->variable[0]],
				serf->pos + option->variable[1] % IDX_MOD);
	serf->spell = 0;
	
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_aff(t_serf *serf, t_option *option)
{
	//ft_printf("aff\n");
	if (option->var_type[0] == REG)
	{
		write_reg(serf, option, 0);
		if (AFF_OP)
			ft_putchar((char)option->variable[0]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_ldi(t_virt *v, t_serf *serf, t_option *option, int save_var)
{
	//ft_printf("ldi\n");
	save_var = option->variable[2];
	write_reg(serf, option, 0);
	if ((option->var_type[1] == REG || option->var_type[1] == DIR)
		&& option->var_type[2] == REG)
	{
		if (serf->spell == LDI)
			serf->reg[save_var] = find_num(v, serf,
				(option->variable[0] + option->variable[1]) % IDX_MOD, 4);
		else if (serf->spell == LLDI)
		{

			serf->reg[save_var] = find_num(v, serf,
				option->variable[0] + option->variable[1], 4);
			set_jump(serf, serf->reg[save_var]);
		}
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		spell_book_with_vars(t_virt *v, t_serf *serf, t_option *option)
{
	if (serf->spell == LD || serf->spell == LLD)
		make_ld(serf, option);
	else if (serf->spell == ADD || serf->spell == SUB)
		make_add_sub(serf, option);
	else if (serf->spell == AND || serf->spell == OR || serf->spell == XOR)
		make_and_or_xor(serf, option, 0);
	else if (serf->spell == ST)
		make_st(v, serf, option);
	else if (serf->spell == STI)
		make_sti(v, serf, option, 0);
	else if (serf->spell == AFF)
		make_aff(serf, option);
	else if (serf->spell == LDI || serf->spell == LLDI)
		make_ldi(v, serf, option, 0);
}

void		spell_book(t_virt *v, t_serf *serf)
{
	//ft_printf("___SPELL___%i\n", serf->id);
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
	if (serf->left_to_cust == -1)
	{
		serf->pos = calс_new_pos(serf->pos + 1);
		serf->left_to_cust = 0;
		serf->spell = 0;
	}
	else
	{
	serf->left_to_cust--;
	if (serf->left_to_cust == 0)
		spell_book(v, serf);
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

t_serf		*find_heir(t_virt *v, t_serf *temp1, t_serf *temp2)
{
	if (v->serf == temp1)
	{
		v->serf = temp1->next;
		free(temp1->reg);
		//ft_printf("kill %i\n", temp1->id);
		free(temp1);
		return(v->serf);
	}
	else
	{
		temp2->next = temp1->next;
		free(temp1->reg);
		//ft_printf("kill %i\n", temp1->id);
		free(temp1);
		return(temp2->next);
	}
	return(NULL);
}

void		kill_serf(t_virt *v, t_serf *temp1, t_serf *temp2)
{
	while (temp1)
	{
		if (v->total_cycles - temp1->last_live_cycle >= v->cycles_before_die)
			temp1 = find_heir(v, temp1, temp2);
		else
		{
			temp2 = temp1;
			temp1 = temp1->next;
		}
	}
}

void			extermination_serfs(t_virt *v)
{
	v->without_abbreviations++;
	kill_serf(v, v->serf, v->serf);
	if (v->life_in_die_cycle >= NBR_LIVE)
	{
		v->cycles_before_die -= CYCLE_DELTA;
		v->without_abbreviations = 0;
	}
	if (v->without_abbreviations >= MAX_CHECKS)
	{
		if (v->hardcore)
			v->cycles_before_die += CYCLE_DELTA;
		else
			v->cycles_before_die -= CYCLE_DELTA;
		v->without_abbreviations = 0;
	}
	v->life_in_die_cycle = 0;
	v->cycles = 0;
}

void		dump_map(t_virt *v, int i, int dump)
{
	if (v->dump > -1)
		dump = 32;
	else
		dump = 64;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i && i % dump == 0)
			ft_printf("\n%6.4#x : ", i);
		ft_printf("%.2x ", v->map[i]);
		++i;
	}
	ft_printf("\n");
	if (!v->vis)
		exit (0);
}

void		hide_show_run(t_virt *v)
{
	while (v->serf)
	{
		v->total_cycles++;
		v->cycles++;
		make_a_move(v, v->serf);
		if (v->cycles == v->cycles_before_die || v->cycles_before_die <= 0)
			extermination_serfs(v);
		if (v->serf && (v->dump == v->total_cycles || v->dump == 0 ||
				v->d == v->total_cycles || v->d == 0))
			dump_map(v, 0, 0);
	}
}

void		winner_is(t_virt *v, t_gamer *gamer)
{
	while (gamer->num != v->player_num_last_say_life)
		gamer = gamer->next;
	ft_printf("Contestant %i, \"%s\", has won !\n", gamer->num, gamer->name);
}

void		send_memory_buffers_to_cl(t_virt *v, t_opencl *o)
{
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
								o->win_size * sizeof(cl_int),
								o->ret_pic, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_map, CL_TRUE, 0,
								MEM_SIZE * sizeof(cl_uchar), v->map,
								0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_log, CL_TRUE,
								0, MEM_SIZE * sizeof(cl_uint),
								v->log, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_serf, CL_TRUE,
								0, MEM_SIZE * sizeof(bool),
								v->have_serf, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_live, CL_TRUE,
								0, MEM_SIZE * sizeof(cl_int),
								v->live_log, 0, NULL, NULL);
	o->ret = clEnqueueWriteBuffer(o->command_queue, o->mem_decor, CL_TRUE,
								0, 285 * sizeof(bool),
								o->decor, 0, NULL, NULL);
	o->ret = clSetKernelArg(o->kernel, 0, sizeof(cl_mem),
							(void *)&o->mem_picture);
	o->ret = clSetKernelArg(o->kernel, 1, sizeof(cl_mem),
							(void *)&o->mem_map);
	o->ret = clSetKernelArg(o->kernel, 2, sizeof(cl_mem),
							(void *)&o->mem_log);
	o->ret = clSetKernelArg(o->kernel, 3, sizeof(cl_mem),
							(void *)&o->mem_serf);
	o->ret = clSetKernelArg(o->kernel, 4, sizeof(cl_mem),
							(void *)&o->mem_live);
	o->ret = clSetKernelArg(o->kernel, 5, sizeof(cl_mem),
							(void *)&o->mem_decor);
}

void		execute_cl(t_virt *v, t_opencl *o, t_mlx *ml)
{
	size_t	i;

	i = o->flows + 1024;
	o->ret = clEnqueueNDRangeKernel(o->command_queue, o->kernel, 1, NULL,
									&i, NULL, 0, NULL, NULL);
	o->ret = clEnqueueReadBuffer(o->command_queue, o->mem_picture, CL_TRUE, 0,
			o->win_size * sizeof(cl_int), o->ret_pic, 0, NULL, NULL);
	i = 0;
	while (i < o->win_size)
	{
		*(int *)(ml->img_adr + i * 4) = o->ret_pic[i];
		i++;
	}
	mlx_put_image_to_window(ml->mlx_ptr, ml->win_ptr, ml->img_ptr, 0, 0);

}

void		send_argument_to_cl(t_virt *v, t_opencl *o)
{
	cl_int	tmp_int;
	send_memory_buffers_to_cl(v, o);
	tmp_int = (cl_int)v->w_x;
	o->ret = clSetKernelArg(o->kernel, 6, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->total_cycles;
	o->ret = clSetKernelArg(o->kernel, 7, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)o->flows;
	o->ret = clSetKernelArg(o->kernel, 8, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->cycles_before_die;
	o->ret = clSetKernelArg(o->kernel, 9, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->mlx->cycle_per_frame;
	o->ret = clSetKernelArg(o->kernel, 10, sizeof(cl_int), &tmp_int);
	tmp_int = (cl_int)v->mlx->sleep_after_frame;
	o->ret = clSetKernelArg(o->kernel, 11, sizeof(cl_int), &tmp_int);
	execute_cl(v, o, v->mlx);
}

int		mouse_move_hook(int x, int y, t_virt *v)
{
	return (0);
}

int		mouse_click_hook(int k, int x, int y, t_virt *v)
{
	return (0);
}

int		say_good_buy(t_virt *v)
{
	exit(0);
	return (0);
}

int		key_press(int key, t_virt *v)
{
	if (key == 53)
		say_good_buy(v);
	if (key == 24 && v->mlx->cycle_per_frame < 99)
	{
		if (v->mlx->sleep_after_frame == 0)
			v->mlx->cycle_per_frame += 1;
		else
			v->mlx->sleep_after_frame -= 1000;
	}
	if (key == 27)
	{
		if (v->mlx->cycle_per_frame > 1)
			v->mlx->cycle_per_frame -= 1;
		else
			v->mlx->sleep_after_frame += 1000;
	}
	return (0);
}

int			start_fight_vis(t_virt *v)
{
	if (v->serf)
	{
		ft_bzero(v->have_serf, MEM_SIZE * sizeof(bool));
		v->total_cycles++;
		v->cycles++;
		make_a_move(v, v->serf);
		if (v->cycles == v->cycles_before_die || v->cycles_before_die <= 0)
			extermination_serfs(v);
		if (v->serf && (v->dump == v->total_cycles || v->dump == 0 ||
				v->d == v->total_cycles || v->d == 0))
			dump_map(v, 0, 0);
		if (v->total_cycles % v->mlx->cycle_per_frame == 0)
			send_argument_to_cl(v, v->opencl);
		usleep(v->mlx->sleep_after_frame);
	}
	else
	{
		winner_is(v, v->gamer);
		mlx_hook(v->mlx->win_ptr, 2, 2, key_press, v);
		mlx_hook(v->mlx->win_ptr, 17, 17, say_good_buy, v);
		mlx_loop(v->mlx->mlx_ptr);
	}
	return(0);
}

void		let_the_show_begin(t_virt *v)
{
	mlx_loop_hook(v->mlx->mlx_ptr, start_fight_vis, v);
	mlx_hook(v->mlx->win_ptr, 2, 2, key_press, v);
	mlx_hook(v->mlx->win_ptr, 17, 17, say_good_buy, v);
	mlx_hook(v->mlx->win_ptr, 4, 4, mouse_click_hook, v);
	mlx_hook(v->mlx->win_ptr, 6, 6, mouse_move_hook, v);
	mlx_loop(v->mlx->mlx_ptr);
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
	winner_is(v, v->gamer);
	exit(0);
}/**/