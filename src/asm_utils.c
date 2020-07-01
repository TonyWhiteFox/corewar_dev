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

#include <stdlib.h>
#include <asm.h>
#include <stdio.h>

void	ft_error(char *err, t_serv *s)
{
	perror(err);
	free(s->line);
	if (s)
		free(s);
	exit(1);
}

