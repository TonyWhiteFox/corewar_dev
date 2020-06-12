/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwanesk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:32:09 by aiwanesk          #+#    #+#             */
/*   Updated: 2017/03/17 13:32:10 by aiwanesk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTECODE_H
# define BYTECODE_H

# include <struct_lex.h>
# include <opcode.h>

/*
** bytecode0.c
*/
void				write_bytecode(unsigned int size);
void				byt_add(char *mem, unsigned int size);
void				byt_new(t_lex *lex);
unsigned int		byt_encode(char *code);

/*
** bytecode1.c
*/
char				*get_arg(char *code);
unsigned int		byt_argument(t_lex *lex, t_op op, unsigned int pos);

/*
** bytecode2.c
*/
int					byt_if_encode(t_op op);
unsigned int		byt_size(t_lex *lex);

#endif
