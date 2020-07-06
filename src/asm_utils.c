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

#include "libft.h"
#include <stdlib.h>
#include <asm.h>
#include <stdio.h>
#include <errno.h>

void			ft_error(char *err, t_serv *s, int err_code)
{
	errno = err_code;
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
			ft_error(ERR_STR_SPLIT, s, EINVAL);
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

static int			ft_int_ovfl(char *num)
{
	size_t			len;
	unsigned int	neg;

	neg = 0;
	if (*num == '-')
	{
		neg = 1;
		num++;
	}
	len = ft_strlen(num);
	if (len < 10)
		return (0);
	else if (len == 10)
	{
		if (num[len - 2] < '4')
			return (0);
		if (num[len - 2] == '4')
		{
			if (!neg && num[len - 1] <= '7')
				return (0);
			else if (neg && num[len - 1] <= '8')
				return (0);
		}
	}
	return (neg ? INT32_MAX : -1);
}

t_bytes				ft_atoi_check(char *nb)
{
	size_t		i;
	t_bytes		ret;

	ret.num = -1;
	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && (nb[1] == 'x' || nb[1] == 'X' || nb[1] == 'b'))
	{
		if (nb[1] == 'x' || nb[1] == 'X')
			ret.unum4 = ft_atoi_base(nb, 16);
		else if (nb[1] == 'b')
			ret.unum4 = ft_atoi_base(nb, 2);
		else
			errno = EDOM;
	}
	else if (!(ret.num = ft_int_ovfl(nb)))
		ret.num = ft_atoi_base(nb, 10);
	return (ret);
}
