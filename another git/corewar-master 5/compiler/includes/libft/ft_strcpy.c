/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:57:55 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/09 19:58:02 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *cpyto, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		cpyto[i] = src[i];
		i++;
	}
	cpyto[i] = '\0';
	return (cpyto);
}
