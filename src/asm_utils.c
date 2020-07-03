/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 21:00:17 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 21:00:19 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include <stdlib.h>
#include <asm.h>
#include <stdio.h>

void			ft_error(char *err, t_serv *s)
{
	perror(err);
	free(s->line);
	if (s)
		free(s);
	exit(1);
}

size_t			len_to_end(t_serv *s, char end)
{
	size_t	len;

	len = 0;
	while (*s->ptr2 != end)
	{
		if (!*s->ptr2++)
			ft_error(ERR_STR_SPLIT, s);
		len++;
	}
	return (len);
}

void			print_tokens(t_serv *s)
{
	t_token		*ptr;

	ptr = s->tokens;
	while (ptr)
	{
		ft_printf("%s :: ", ptr->content);
		ptr = ptr->next;
	}
}
