/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:05:32 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:34 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"

t_instr			*init_instr(t_serv *s)
{
	t_instr		*new;
	int			i;

	i = -1;
	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s);
	new->label = NULL;
	new->op = NULL;
	while (++i < 3)
	{
		new->args[i].type = 0;
		new->args[i].value = INT32_MAX;
		new->args[i].label = NULL;
	}
	new->byte = 0;
	new->next = NULL;
	return (new);
}

t_op			*get_op(char *name)
{
	size_t		i;

	i = 0;
	while (i < (sizeof(g_op) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
}

void			add_instr(t_serv *s, t_instr *new)
{
	t_instr		*ptr;

	if (!s->instr)
		s->instr = new;
	else
	{
		ptr = s->instr;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

static void		set_size(t_serv *s)
{
	t_instr		*ptr;
	int			i;
	int			arg;

	ptr = s->instr;
	while (ptr)
	{
		i = -1;
		arg = 0;
		while (++i < 3)
		{
			if (ptr->args[i].value != INT32_MAX || ptr->args[i].label)
			{
				if (ptr->args[i].type == T_DIR)
					arg += ptr->op->t_dir_size;
				else
					arg++;
			}
		}
		ptr->byte = s->header.prog_size;
		ptr->size = 1 + (ptr->op->args_types_code ? 1 : 0) + arg;
		s->header.prog_size += ptr->size;
		ptr = ptr->next;
	}
}

void			parser(t_serv *s)
{
	s->tok_ptr = s->tokens;
	while (s->tok_ptr)
	{
		if (s->tok_ptr->type == PROG_NAME)
			parse_prog_name(s);
		else if (s->tok_ptr->type == NEW_LINE && s->last_instr
				&& s->last_instr->op)
			s->last_instr = NULL;
		else if (s->tok_ptr->type == PROG_COMMENT)
			parse_prog_comment(s);
		else if (s->tok_ptr->type == STRING)
			parse_string(s);
		else if (s->tok_ptr->type == COMMENT)
		{
			s->tok_ptr = s->tok_ptr->next;
			continue;
		}
		s->tok_ptr = s->tok_ptr->next;
	}
	set_size(s);
}
