/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:05:25 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:26 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

static void		parse_label(t_serv *s)
{
	char	*split;
	char	*split2;
	char	*ptr;
	size_t	i;

	split = NULL;
	split2 = NULL;
	if ((split = ft_strchr(s->line, LABEL_CHAR)))
	{
		ptr = s->line;
		i = 0;
		while (ptr != split)
		{
			if (!ft_strchr(LABEL_CHARS, *ptr))
				ft_error(ERR_WRONG_LABEL, s);
			i++;
			ptr++;
		}
		s->last_instr->label = ft_strndup(s->line, i);
	}
	if (split++ && (split2 = ft_strchr(split, LABEL_CHAR)))
		ft_error(ERR_DOUBLE_LABEL, s);
}

static void		translate(t_serv *s)
{
	t_instr		*instr;
	t_instr		*ptr;

	if (!(instr = (t_instr *)malloc(sizeof(*instr))))
		ft_error(ERR_MALLOC, s);
	instr->label = NULL;
	instr->next = NULL;
	s->last_instr = instr;
	if (!s->instr)
		s->instr = instr;
	else
	{
		ptr = s->instr;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = instr;
	}
	parse_label(s);
}

void			lexer(t_serv *s)
{
	int		size;

	while (1)
	{
		free(s->line);
		s->line = NULL;
		if ((size = get_next_line(s->fd, &s->line)) < 1)
			break ;
		translate(s);
	}
	if (size < 0)
		ft_error(ERR_READ_EMPTY, s);
}
