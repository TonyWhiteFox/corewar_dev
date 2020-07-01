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

# include <stdlib.h>
# include "op.h"

# define ERR_OPEN_FILE		"ERROR: Can\'t open file"
# define ERR_MALLOC			"ERROR: Can\'t allocate memory"
# define ERR_READ_FILE		"ERROR: Incorrect input file"
# define ERR_DOUBLE_LABEL	"ERROR: Excessive label delimiter, expected 1"
# define ERR_WRONG_LABEL	"ERROR: Incorrect label name"
# define ERR_STR_SPLIT		"ERROR: Can\'t identify tokens in the line"
# define FLAG_LABEL			1
# define FLAG_ARG			2
# define FLAG_CHAMP_NAME	4
# define FLAG_CHAMP_COMM	8
# define READ_SIZE			4096

typedef enum				e_type
{
	IDENTIFER,
	STRING,
	COMMENT,
	COMMAND,
	DIRECT,
	NUM,
	REGISTER,
	SEPARATOR,
	NEW_LINE,
	QUOTE,
	PROG_NAME,
	PROG_COMMENT,
	LABEL,

	OPERATOR,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	END,
	WHITESPACE,
}							t_type;


typedef struct				s_token
{
	t_type					type;
	char					*content;
	struct s_token			*next;
}							t_token;

typedef struct				s_serv
{
	int						fd;
	char					*line;
	char					buff[READ_SIZE + 1];
	char					*ptr1;
	char					*ptr2;
	struct header_s			header;
	struct s_instr			*instr;
	struct s_instr			*last_instr;
	t_type 					ptr_flag;
	struct s_list			*memguru;
	struct s_list			*last_sentence;
	struct s_token			*tokens;

}							t_serv;

typedef struct				s_instr
{
	struct s_op				type;
	struct s_list			*sentence;
	char					*label;
	int						opcode;
	int						arg1;
	int						arg2;
	int						arg3;
	struct s_instr			*next;
}							t_instr;

void						lexer(t_serv *s);
void						parser(t_serv *s);
void						output(t_serv *s);
void						ft_error(char *err, t_serv *s);
int							get_word_len(char const *str, char *c);
void						ft_lstpushback(struct s_list **begin_list, struct
							s_list *new);
void						*ft_memguru(size_t size, struct s_list **list);
void						*ft_memguru_add_arr(void **arr, size_t arr_size,
							struct s_list **list);
void						*ft_memguru_add(void *ptr, struct s_list **list);
t_instr						*init_instr(t_serv *s, struct s_op op);

#endif
