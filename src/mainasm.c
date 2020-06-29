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

static void	init_s(t_serv *s)
{
	s->fd = -1;
	s->line = NULL;
	s->instr = NULL;
	s->last_instr = NULL;
}

static void	print_usage(void)
{
	ft_printf("Usage: ./asm (champion.s|champion.cor)\n");
}

int			main(int argc, char **argv)
{
	size_t	len;
	t_serv	*s;

	if (argc == 2 && (len = ft_strlen(argv[1])) && argv[1][len - 2] == '.'
		&& argv[1][len - 1] == 's')
	{
		if (!(s = malloc(sizeof(*s))))
			ft_error(ERR_MALLOC, s);
		init_s(s);
		if ((s->fd = open(argv[1], O_RDONLY)) == -1)
			ft_error(ERR_OPEN_FILE, s);
		lexer(s);
		parser(s);
		output(s);
		free(s);
	}
	else
		print_usage();
	return (0);
}
