/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffloris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:37:01 by ffloris           #+#    #+#             */
/*   Updated: 2018/06/17 17:37:02 by ffloris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		free_processes(t_process *processes)
{
	t_process	*prev;

	while (processes)
	{
		prev = processes;
		processes = processes->next;
		free(prev);
	}
}
