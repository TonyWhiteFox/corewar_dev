/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:49:53 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 22:49:57 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"

void	parse_reg(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_REG;
	s->last_instr->args[i].value = ft_atoi(&s->tok_ptr->content[1]);
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_ind(t_serv *s, int i)
{
	s->last_instr->args[i].type = T_IND;
	s->last_instr->args[i].value = ft_atoi(s->tok_ptr->content);
	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr->type == NUM)
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

void	parse_dir(t_serv *s, int i)
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

void	parse_arg(t_serv *s, int i)
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
	else if (s->tok_ptr->type == NUM || s->tok_ptr->type == LABEL)
		parse_ind(s, i);
	else
		ft_error(ERR_PARSE_ARG, s);
}

void	parse_arguments(t_serv *s)
{
	int			i;

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
