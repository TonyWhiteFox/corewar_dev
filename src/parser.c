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
	new->next = NULL;
	return (new);
}

t_op			*get_op(char *name)
{
	int		i;

	i = 0;
	while (i < (sizeof(g_op) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op[i].name, name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
}

static void		add_instr(t_serv *s, t_instr *new)
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

static void	parse_prog_comment(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == STRING)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (!len || len > COMMENT_LENGTH)
			ft_error(ERR_COMMENT_LEN, s);
		ft_strcpy(s->header.comment, s->tok_ptr->content);
	}
	else
		ft_error(ERR_COMMENT_LEN, s);
}

static void	parse_prog_name(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == STRING)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (!len || len > PROG_NAME_LENGTH)
			ft_error(ERR_NAME_LEN, s);
		ft_strcpy(s->header.prog_name, s->tok_ptr->content);
	}
	else
		ft_error(ERR_NAME_LEN, s);
}
static void	parse_reg(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_REG;
	s->last_instr->args[i].value = ft_atoi(&s->tok_ptr->content[1]);
	s->tok_ptr = s->tok_ptr->next;
}

static void	parse_ind(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_IND;
	s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
	s->tok_ptr = s->tok_ptr->next;
}

static void	parse_dir(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_DIR;
	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == NUM
		|| (s->tok_ptr->type == STRING && ft_isnumber(s->tok_ptr->content)))
		s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
	else if (s->tok_ptr->type == LABEL)
	{
		s->tok_ptr = s->tok_ptr->next;
		if (s->tok_ptr->type == STRING || s->tok_ptr->type == NUM)
			s->last_instr->args[i].label = s->tok_ptr->content;
		else
			ft_error(ERR_PARSE_DIR, s);
	}
	else
		ft_error(ERR_PARSE_ARG, s);
	s->tok_ptr = s->tok_ptr->next;
}

static int8_t	get_arg_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

static void	parse_label_arg(t_serv *s)
{

}

static void	parse_arg(t_serv *s, int i)
{
	if (s->tok_ptr->type == DIRECT)
		parse_dir(s, i);
	else if (s->tok_ptr->type == STRING)
	{
		if (s->tok_ptr->content[0] == REG_CHAR)
			parse_reg(s, i);
		else if (ft_isnumber(s->tok_ptr->content))
			s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
		else
			ft_error(ERR_PARSE_ARG, s);
	}
	else if (s->tok_ptr->type == LABEL)
		parse_label_arg(s);
	else if (s->tok_ptr->type == NUM)
		parse_ind(s, i);
	else
		ft_error(ERR_PARSE_ARG, s);
}

static void	parse_arguments(t_serv *s)
{
	int			i;
	t_op		*op;

	i = 0;
	s->tok_ptr = s->tok_ptr->next;
	while (s->tok_ptr->type != NEW_LINE)
	{
		parse_arg(s, i++);
		if (s->tok_ptr->type == SEPARATOR || s->tok_ptr->type == COMMENT)
			s->tok_ptr = s->tok_ptr->next;
		else if (s->tok_ptr->type == NEW_LINE)
			break ;
		else
			ft_error(ERR_PARSE_ARG, s);
	}
	s->last_instr = NULL;
}

static void	parse_label(t_serv *s)
{
	t_instr		*new;

	new = init_instr(s);
	new->label = s->tok_ptr->content;
	add_instr(s, new);
	s->last_instr = new;
	s->tok_ptr = s->tok_ptr->next;
}

static int		parse_op(t_serv *s)
{
	t_instr		*new;
	t_op		*op;

	if ((op = get_op(s->tok_ptr->content)))
	{
		if (s->last_instr)
			s->last_instr->op = op;
		else
		{
			new = init_instr(s);
			new->op = op;
			add_instr(s, new);
			s->last_instr = new;
		}
		return (1);
	}
	return (0);
}

static void	parse_str(t_serv *s)
{
	if (parse_op(s))
		parse_arguments(s);
	else if (s->tok_ptr->next->type == LABEL)
		parse_label(s);
	else
		ft_error(ERR_PARSE_STRING, s);
}

static void	parse_all_labels(t_serv *s)
{

}

static void set_size(t_serv *s)
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
		ptr->size = 1 + (ptr->op->args_types_code ? 1 : 0) + arg;
		s->header.prog_size += ptr->size;
		ptr = ptr->next;
	}
}

void		parser(t_serv *s)
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
			parse_str(s);
		else if (s->tok_ptr->type == COMMENT)
		{
			s->tok_ptr = s->tok_ptr->next;
			continue;
		}
		s->tok_ptr = s->tok_ptr->next;
	}
	parse_all_labels(s);
	set_size(s);
}
