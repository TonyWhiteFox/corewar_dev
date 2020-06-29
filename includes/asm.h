/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:36:51 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/02/29 19:18:00 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define ERR_OPEN_FILE		"ERROR: Can\'t open file"
# define ERR_MALLOC			"ERROR: Can\'t allocate memory"
# define ERR_READ_EMPTY		"ERROR: Empty input"
# define ERR_DOUBLE_LABEL	"ERROR: Excessive label delimiter, expected 1"
# define ERR_WRONG_LABEL	"ERROR: Incorrect label name"

typedef struct				s_serv
{
	int						fd;
	char					*line;
	struct s_instr			*instr;
	struct s_instr			*last_instr;

}							t_serv;

typedef struct				s_instr
{
	char					*label;
	int						opcode;
	int						reg;
	int						direct;
	char					*indirect;
	struct s_instr			*next;
}							t_instr;

void						lexer(t_serv *s);
void						parser(t_serv *s);
void						output(t_serv *s);
void						ft_error(char *err, t_serv *s);
#endif
