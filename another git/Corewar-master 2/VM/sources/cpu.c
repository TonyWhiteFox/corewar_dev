/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwanesk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:20:54 by aiwanesk          #+#    #+#             */
/*   Updated: 2017/03/22 16:52:22 by aiwanesk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cpu.h"

static void			fct_cpu(t_fct_cpu fct[17])
{
	fct[0] = NULL;
	fct[1] = &apply_live;
	fct[2] = &apply_ld;
	fct[3] = &apply_st;
	fct[4] = &apply_add;
	fct[5] = &apply_sub;
	fct[6] = &apply_and;
	fct[7] = &apply_or;
	fct[8] = &apply_xor;
	fct[9] = &apply_zjmp;
	fct[10] = &apply_ldi;
	fct[11] = &apply_sti;
	fct[12] = &apply_fork;
	fct[13] = &apply_lld;
	fct[14] = &apply_lldi;
	fct[15] = &apply_lfork;
	fct[16] = &apply_aff;
}

static void			get_cycles(int32_t cycles[17])
{
	cycles[0] = 0;
	cycles[1] = 10;
	cycles[2] = 5;
	cycles[3] = 5;
	cycles[4] = 10;
	cycles[5] = 10;
	cycles[6] = 6;
	cycles[7] = 6;
	cycles[8] = 6;
	cycles[9] = 20;
	cycles[10] = 25;
	cycles[11] = 25;
	cycles[12] = 800;
	cycles[13] = 10;
	cycles[14] = 50;
	cycles[15] = 1000;
	cycles[16] = 2;
}

void				cpu(t_process *process, t_env *env)
{
	static t_fct_cpu	cpu[17] = {0};
	static int32_t		cycles[17] = {0};
	static int			init = 0;
	int32_t				opcode;

	process->pc = process->pc % MEM_SIZE;
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	if (init == 0 && ++init)
	{
		fct_cpu(cpu);
		get_cycles(cycles);
	}
	opcode = env->memory[process->pc % MEM_SIZE];
	if (opcode <= 16 && cpu[opcode] && process->nb_cycle >= cycles[opcode])
	{
		cpu[opcode](process, env);
		protocol_pc(*env, *process, process->pc);
	}
	else if (opcode > 16 || !cpu[opcode])
	{
		process->nb_cycle -= 1;
		++process->pc;
	}
	process->pc = process->pc % MEM_SIZE;
}
