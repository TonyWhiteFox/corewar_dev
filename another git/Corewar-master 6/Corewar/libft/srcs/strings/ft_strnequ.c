/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:28:55 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:11 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	if (!n)
		return (1);
	n--;
	while ((*s1 && *s2) && *s1 == *s2 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}
