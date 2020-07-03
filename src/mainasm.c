/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainasm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:03:50 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:59 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static void		init_s(t_serv *s)
{
	s->fd = -1;
	s->fd_out = -1;
	s->flag = 0;
	s->filename = NULL;
	s->line = NULL;
	s->instr = NULL;
	s->last_instr = NULL;
	s->ptr_flag = 0;
	s->memguru = NULL;
	s->last_sentence = NULL;
	s->header.magic = COREWAR_EXEC_MAGIC;
}

static void		print_usage(void)
{
	ft_printf("Usage: ./asm <champion>.s [-a|-d]\n");
	ft_printf("\t\t-a\tDump annotated program on standard output\n");
	ft_printf("\t\t-d\tDebug mode\n");
}

static t_serv	*read_file(char *file)
{
	size_t		len;
	t_serv		*s;

	if ((len = ft_strlen(file)) && file[len - 2] == '.' && file[len - 1] == 's')
	{
		if (!(s = malloc(sizeof(*s))))
			ft_error(ERR_MALLOC, s);
		init_s(s);
		s->filename = ft_strdup(file);
		ft_memguru_add(s->filename, &s->memguru);
		if ((s->fd = open(file, O_RDONLY)) == -1)
			ft_error(ERR_OPEN_FILE, s);
		return (s);
	}
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_serv	*s;
	int		i;

	if (argc > 1 && (s = read_file(argv[1])))
	{
		i = 1;
		while (++i < argc)
		{
			if (!ft_strcmp(argv[i], "-a"))
				s->flag |= FLAG_DUMP;
			if (!ft_strcmp(argv[i], "-d"))
				s->flag |= FLAG_DEBUG;
		}
		lexer(s);
		parser(s);
		output(s);
		free(s);
	}
	else
		print_usage();
	return (0);
}
