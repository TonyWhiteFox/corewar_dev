/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:53:01 by lshellie          #+#    #+#             */
/*   Updated: 2020/03/19 18:09:47 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_file_format(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (len == 4 && ft_strcmp(str, ".cor"))
		return (0);
	if (len > 4 && ft_strcmp(&str[len - 4], ".cor"))
		return (0);
	return (1);
}

int			parse_all(int fd, t_main *m)
{
	t_player	*new;

	if (!(new = choose_player(m)))
		return (0);
	if (!(get_header(fd)))
		return (0);
	if (!(get_name_or_comment(new, fd, GET_NAME)))
		return (0);
	if (!(get_null(fd)))
		return (0);
	if (!(get_size(new, fd)))
		return (0);
	if (!(get_name_or_comment(new, fd, GET_COMMENT)))
		return (0);
	if (!(get_null(fd)))
		return (0);
	if (!(get_code(new, fd)))
		return (0);
	return (1);
}

int			read_player(t_main *m, char *str)
{
	int		fd;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (ft_error(CANT_OPEN_FILE));
	if (!(parse_all(fd, m)))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int			read_files(t_main *m, int ac, char **av, int i)
{
	while (++i < ac)
	{
		if (find_dump_vis_flags(m, ac, av, &i))
			continue ;
		if (!ft_strcmp(av[i], "-n") && i + 2 < ac)
		{
			i += 2;
			continue ;
		}
		if (check_file_format(av[i]))
		{
			if (!(read_player(m, av[i])))
				return (0);
		}
		else
			return (ft_error(BAD_FILE_FORMAT));
	}
	if (m->v_flag)
		m->dump = -1;
	return (1);
}

int			manage_n(t_main *m, int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-n") && i + 2 < ac && is_number(av[i + 1]))
		{
			m->n_flag = ft_atoi(av[++i]);
			if (!(m->n_flag > 0 && m->n_flag <= MAX_PLAYERS))
				return (ft_error(BAD_FLAG));
			if (check_file_format(av[++i]))
			{
				if (!(read_player(m, av[i])))
					return (0);
			}
			else
				return (ft_error(BAD_FILE_FORMAT));
		}
	}
	return (1);
}
