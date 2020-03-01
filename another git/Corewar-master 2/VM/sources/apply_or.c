/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwanesk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:11:32 by aiwanesk          #+#    #+#             */
/*   Updated: 2017/03/22 16:46:48 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

/*
** or : Cette oprocessération est un OU bit-à-bit,
** suivant le même processrinciprocesse que and, son
** oprocesscode est donc évidemment 7.
*/

static void		dbg(t_process *proc, int32_t val1, int32_t val2, int32_t val3)
{
	ft_putstr("P\t");
	ft_putstr("\033[1;");
	ft_putnbr((31 + (proc->idlive % 7)));
	ft_putstr(";40m");
	ft_putnbr(proc->id);
	ft_putstr(" | or ");
	ft_putnbr(val1);
	ft_putstr(" ");
	ft_putnbr(val2);
	ft_putstr(" ");
	ft_putnbr(val3);
	ft_putendl("");
	ft_putstr(C_NONE);
}

void			apply_or(t_process *process, t_env *env)
{
	t_args		args[3];
	int32_t		pc;
	int32_t		val1;
	int32_t		val2;
	int32_t		reg;

	decode(args, env->memory[process->pc], env->memory[process->pc + 1]);
	pc = process->pc + BYPASS_ARG_ENCODE;
	val1 = get_args(env->memory, pc, args[0].length);
	val1 = return_value(process, env->memory, args[0], val1);
	pc += args[0].length;
	val2 = get_args(env->memory, pc, args[1].length);
	val2 = return_value(process, env->memory, args[1], val2);
	pc += args[1].length;
	reg = get_args(env->memory, pc, args[2].length);
	if (reg > 0 && reg <= REG_NUMBER)
		process->reg[reg - 1] = (val1 | val2);
	process->nb_cycle -= 6;
	process->pc += BYPASS(args, BYPASS_ARG_ENCODE);
	process->pc %= MEM_SIZE;
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	process->carry = ((val1 | val2) == 0);
	if (env->dbg)
		dbg(process, val1, val2, reg);
}
