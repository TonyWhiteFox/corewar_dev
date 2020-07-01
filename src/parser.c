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

t_instr		*init_instr(t_serv *s, t_op op)
{
	t_instr		*new;

	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s);
	new->type = op;
	new->label = NULL;
	new->opcode = 0;
	new->arg1 = 0;
	new->arg2 = 0;
	new->arg3 = 0;
	new->next = NULL;
	return (new);
}

t_op			*get_op(char *name)
{
	unsigned	i;

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

	ptr = s->instr;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void		parser(t_serv *s)
{

}
