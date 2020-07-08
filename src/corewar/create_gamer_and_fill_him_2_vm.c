/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_gamer_and_fill_him_2_vm.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:38:37 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/04 12:45:34 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_body(t_virt *v, t_gamer *new_gamer, int readed_byte, char test_for_read)
{
	new_gamer->code = (char *)malloc(new_gamer->size + 1);
	ft_bzero(new_gamer->code, new_gamer->size + 1);
	if ((readed_byte = read(v->fd, new_gamer->code, new_gamer->size)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
	if ((readed_byte != new_gamer->size) ||
			((read(v->fd, &test_for_read, 1)) > 0))
		close_fd_send_error_close(v, "Champion's size in file is false");
}

void		read_comment(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->comment = (char *)malloc(2049);
	ft_bzero(new_gamer->comment, 2049);
	if ((read(v->fd, new_gamer->comment, 2048)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
}

void		read_size(t_virt *v, t_gamer *new_gamer)
{
	new_gamer->size = get_int_in_fd(v, 0, 0, 0);
	if (new_gamer->size < 0 || new_gamer->size > CHAMP_MAX_SIZE)
		close_fd_send_error_close(v, "Invalid champion's size!");
}