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
#include <errno.h>

t_instr			*init_instr(t_serv *s)
{
	t_instr		*new;
	int			i;

	i = -1;
	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s, ENOMEM);
	new->label = NULL;
	new->op = NULL;
	while (++i < 3)
	{
		new->args[i].type = 0;
		new->args[i].value.num = 0;
		new->args[i].label = NULL;
	}
	new->byte = 0;
	new->acb = 0;
	new->size = 0;
	new->next = NULL;
	return (new);
}

t_op			*get_op(char *name)
{
	size_t		i;

	i = 0;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op_tab[i].name, name))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

static void		set_size(t_serv *s, t_instr *ptr)
{
	int			i;
	int			arg;

	if (ptr && ptr->op)
	{
		i = -1;
		arg = 0;
		while (++i < 3)
		{
			if (ptr->args[i].type)
			{
				if (ptr->args[i].type == T_IND || (ptr->args[i].type == T_DIR
				&& ptr->op->reduced_dir_size))
					arg += 2;
				else if (ptr->args[i].type == T_DIR &&
				!ptr->op->reduced_dir_size)
					arg += 4;
				else
					arg++;
			}
		}
		ptr->byte = s->header.prog_size;
		ptr->size++;
		if (ptr->op)
			ptr->size += (ptr->op->is_acb ? 1 : 0) + arg;
		s->header.prog_size += ptr->size;
	}
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
	if (new->op && new->op->is_acb)
		new->acb = arg_coding_byte(new);
	set_size(s, new);
	if (s->flag & FLAG_INSTR)
		print_instr(s->last_instr);
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
		{
			add_instr(s, s->last_instr);
			s->last_instr = NULL;
		}
		else if (s->tok_ptr->type == PROG_COMMENT)
			parse_prog_comment(s);
		else if (s->tok_ptr->type == LABEL)
			parse_label(s);
		else if (s->tok_ptr->type == STRING)
			parse_string(s);
		else if (s->tok_ptr->type == COMMENT)
		{
			s->tok_ptr = s->tok_ptr->next;
			continue;
		}
		s->tok_ptr = s->tok_ptr->next;
	}
	code_labels(s);
}
