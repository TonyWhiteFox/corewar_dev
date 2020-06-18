/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:04:13 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/18 21:54:44 by ldonnor-         ###   ########.fr       */
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

void		init_start_params(t_virt *v)
{
	v->d = -1;
	v->dump = -1;
	v->vis = false;
	v->total_gamers = 0;
	v->gamer = NULL;
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
	if ((read(v->fd, new_gamer->comment, 128)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
}

void		read_body(t_virt *v, t_gamer *new_gamer, int readed_byte)
{
	char	test_for_read;

	new_gamer->code = (char *)malloc(new_gamer->size + 1);
	ft_bzero(new_gamer->code, new_gamer->size + 1);
	if ((readed_byte = read(v->fd, new_gamer->code, new_gamer->size)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
	/*if ((readed_byte != new_gamer->size) ||
			((read(v->fd, &test_for_read, 1)) > 0))*/
		ft_printf("%i %i %i\n", readed_byte, new_gamer->size, read(v->fd, &test_for_read, 10000));
		close_fd_send_error_close(v, "Champion's size in file is false");
}

int		get_code2(t_gamer *new_gamer, int fd)
{
	char	buf[new_gamer->size + 1];
	int		ret;

	if ((ret = read(fd, buf, new_gamer->size)) < 0)
		return (ft_error(READ_ERROR));
	buf[ret] = 0;
	if (ret != new_gamer->size)
		return (ft_error(INV_CHAP_SIZE));
	if (!(new_gamer->code = ft_strndup(buf, ret)))
		return (ft_error(INVALID_MALLOC));
	if (read(fd, buf, 1) > 0)
		return (ft_error(INV_CHAP_SIZE));
	return (1);
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

	// char	buf[4];
	// char	str[4];

	// i = -1;
	// read(v->fd, buf, 4);
	// while (++i < 4)
	// 	str[i] = buf[3 - i];
	// return(*((int *)str));
}

void		read_size(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->size = get_int_in_fd(v, 0, 0, 0);
	if (new_gamer->size <= 0 || new_gamer->size > CHAMP_MAX_SIZE)
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
	read_body(v, new_gamer, 0);
	// get_code2(new_gamer, v->fd);
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
}/**/