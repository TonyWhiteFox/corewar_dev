/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:55:12 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 21:55:53 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_islower(int c)
{
	if (97 <= c && c <= 122)
		return (1);
	else
		return (0);
}