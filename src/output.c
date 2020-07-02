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

static void		write_code(t_serv *s)
{

}

static void		print_arg(t_instr *ptr, int i)
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

static void		print_code(t_serv *s)
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
	write_code(s);
	if (s->flag & FLAG_DUMP)
		print_code(s);
	free(file);
}
