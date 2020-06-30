/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:45:51 by mmanhack          #+#    #+#             */
/*   Updated: 2019/10/07 13:05:28 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_word_len(char const *str, char *c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ft_strchr(c, str[i]))
		i++;
	while (!ft_strchr(c, str[i]) && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

void	ft_lstpushback(t_list **begin_list, t_list *new)
{
	t_list *temp;

	if (!*begin_list)
		*begin_list = new;
	else
	{
		temp = *begin_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
