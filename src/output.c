/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 21:31:45 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 21:31:55 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

static void		code_arg(t_serv *s, t_instr *ptr, int i)
{
	uint32_t	uint;

	if (ptr->args[i].type == T_DIR)
	{
		if (ptr->args[i].label)
			uint = big_endian(get_offset(s, ptr, ptr->args[i].label));
		else
			uint = big_endian(ptr->args[i].value);
		write(s->fd, &uint, ptr->op->t_dir_size);
	}
	else if (ptr->args[i].type == T_IND)
	{
		if (ptr->args[i].label)
		{
			uint = big_endian(get_offset(s, ptr, ptr->args[i].label));
			write(s->fd, &uint, 2);
		}
		else
		{
			uint = big_endian(ptr->args[i].value);
			write(s->fd, &uint, 2);
		}
	}
	else if (ptr->args[i].type == T_REG)
		write(s->fd_out, &ptr->args[i].value, 1);
}

static void		code_instr(t_serv *s)
{
	t_instr		*ptr;
	char		abc;
	int			i;

	ptr = s->instr;
	while (ptr)
	{
		write(s->fd_out, &ptr->op->code, 1);
		if (ptr->op->args_types_code)
		{
			abc = arg_coding_byte(ptr);
			write(s->fd_out, &abc, 1);
		}
		i = -1;
		while (++i < 3 && (ptr->args[1].value != INT32_MAX
				|| ptr->args[i].label))
			code_arg(s, ptr, i);
		ptr = ptr->next;
	}
}

static void		code_header(t_serv *s)
{
	uint32_t	uint;

	uint = big_endian(s->header.magic);
	write(s->fd_out, &uint, 4);
	write(s->fd_out, s->header.prog_name, PROG_NAME_LENGTH);
	write(s->fd_out, "\0\0\0\0", 4);
	uint = big_endian(s->header.prog_size);
	write(s->fd_out, &uint, 4);
	write(s->fd_out, s->header.comment, COMMENT_LENGTH);
	write(s->fd_out, "\0\0\0\0", 4);
}

static void		byte_code(t_serv *s)
{
	code_header(s);
	code_instr(s);
}

void			output(t_serv *s)
{
	char	*file;
	char	*tmp;
	size_t	len;

	len = ft_strlen(s->filename);
	if (!(tmp = ft_strndup(s->filename, len - 2)))
		ft_error(ERR_MALLOC, s);
	if (!(file = ft_strjoin(tmp, ".cor")))
		ft_error(ERR_MALLOC, s);
	if ((s->fd_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error(ERR_CREATE_FILE, s);
	ft_printf("Writing output program to %s\n", file);
	byte_code(s);
	close(s->fd_out);
	if (s->flag & FLAG_DUMP)
		print_code(s);
	free(file);
}
