/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 23:06:06 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 23:06:10 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int				get_offset(t_serv *s, t_instr *instr, char *label)
{
	t_instr		*ptr;

	ptr = s->instr;
	while (ptr)
	{
		if (label && ptr->label && !ft_strcmp(label, ptr->label))
			break ;
		ptr = ptr->next;
	}
	return (ptr->byte - instr->byte);
}

uint32_t		arg_coding_byte(t_instr *ptr)
{
	uint32_t	ret;

	ret = 0;
	ret |= ptr->args[0].type;
	ret = ret << 3;
	ret |= ptr->args[1].type;
	ret = ret << 2;
	ret |= ptr->args[2].type;
	ret = ret << 1;
	return (ret);
}

uint32_t		big_endian(uint32_t num)
{
	uint32_t	b0;
	uint32_t	b1;
	uint32_t	b2;
	uint32_t	b3;
	uint32_t	res;

	b0 = (num & 0x000000ff) << 24u;
	b1 = (num & 0x0000ff00) << 8u;
	b2 = (num & 0x00ff0000) >> 8u;
	b3 = (num & 0xff000000) >> 24u;
	res = b0 | b1 | b2 | b3;
	return (res);
}

void			print_arg(t_instr *ptr, int i)
{
	if (ptr->args[i].type == T_DIR)
		write(1, "%", 1);
	else if (ptr->args[i].type == T_REG)
		write(1, "r", 1);
	if (ptr->args[i].label)
		ft_printf(":%-16s", ptr->args[i].label);
	else
		ft_printf("%-17d", ptr->args[i].value);
}

void			print_instr(t_instr *ptr)
{
	int		j;

	if (ptr)
	{
		if (ptr->label)
			ft_printf("%-10d:    %s:\n", ptr->byte, ptr->label);
		ft_printf("%-5d(%-2d) :        ", ptr->byte, ptr->size);
		ft_printf("%-10s", ptr->op->name);
		j = -1;
		while (++j < 3 && ptr->args[j].type)
			print_arg(ptr, j);
		ft_printf("\n");
		ptr = ptr->next;
	}
}

void			print_code(t_serv *s)
{
	t_instr		*ptr;
	size_t		i;
	int			j;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", s->header.prog_size);
	ft_printf("Name : \"%s\"\n", s->header.prog_name);
	ft_printf("Comment : \"%s\"\n", s->header.comment);
	i = 0;
	ptr = s->instr;
	while (ptr)
	{
		if (ptr->label)
			ft_printf("%-10d:    %s:\n", i, ptr->label);
		ft_printf("%-5d(%-2d) :        ", i, ptr->size);
		ft_printf("%-10s", ptr->op->name);
		j = -1;
		while (++j < 3 && (ptr->args[j].value != INT32_MAX
		|| ptr->args[j].label))
			print_arg(ptr, j);
		ft_printf("\n");
		i += ptr->size;
		ptr = ptr->next;
	}
}
