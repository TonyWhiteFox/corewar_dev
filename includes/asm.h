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
# define ERR_WRONG_VALUE	"ERROR: Incorrect value, integer expected"
# define ERR_STR_SPLIT		"ERROR: Can\'t identify tokens in the line"
# define ERR_NAME_LEN		"ERROR: Incorrect program name"
# define ERR_COMMENT_LEN	"ERROR: Incorrect program comment"
# define ERR_PARSE_STRING	"ERROR: Incorrect string token"
# define ERR_CREATE_FILE	"ERROR: Can\'t create output file"
# define ERR_PARSE_ARG		"ERROR: Can\'t parse argument"
# define ERR_PARSE_ARG_NUM	"ERROR: Wrong number of arguments"
# define ERR_PARSE_DIR		"ERROR: STRING token expected after %"
# define ERR_REG			"ERROR: Incorrect REGISTER argument value"
# define ERR_NO_LABEL		"ERROR: No such label"
# define ERR_COMMAND		"ERROR: Undefined command"
# define FLAG_LABEL			1
# define FLAG_ARG			2
# define FLAG_CHAMP_NAME	4
# define FLAG_CHAMP_COMM	8
# define READ_SIZE			4096
# define FLAG_DUMP			1
# define FLAG_DEBUG			2
# define FLAG_INSTR			4
# define HEX_CHARS			"0123456789abcdef"

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
	LABEL_REF,

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

typedef union				u_bytes
{
	int						num;
	int8_t					num1;
	int16_t					num2;
	int32_t					num4;
	uint8_t					unum1;
	uint16_t				unum2;
	uint32_t				unum4;
	unsigned char			bytes[4];
}							t_bytes;

typedef struct				s_serv
{
	int						fd;
	int						fd_out;
	int						flag;
	size_t					i_line;
	size_t					out_line;
	char					*filename;
	char					*line;
	char					*buff;
	char					*ptr1;
	char					*ptr2;
	struct s_list			*arg_labels;
	t_token					*tok_ptr;
	struct s_header			header;
	struct s_instr			*instr;
	struct s_instr			*last_instr;
	t_type					ptr_flag;
	struct s_list			*memguru;
	struct s_list			*last_sentence;
	struct s_token			*tokens;

}							t_serv;

typedef struct				s_arg
{
	t_arg_type				type;
	t_bytes					value;
	char					*label;
	size_t					code_size;
	t_bytes 				code;
}							t_arg;

typedef struct				s_instr
{
	char					*label;
	struct s_op				*op;
	struct s_arg			args[3];
	unsigned char			acb;
	size_t					size;
	size_t					byte;
	struct s_instr			*next;
}							t_instr;

void						lexer(t_serv *s);
void						parser(t_serv *s);
void						output(t_serv *s);
void						ft_error(char *err, t_serv *s);
void						*ft_memguru(size_t size, struct s_list **list);
void						*ft_memguru_add_arr(void **arr, size_t arr_size,
							struct s_list **list);
void						*ft_memguru_add(void *ptr, struct s_list **list);
t_instr						*init_instr(t_serv *s);
void						parse_num(t_serv *s);
void						parse_comment(t_serv *s);
void						parse_str(t_serv *s);
void						parse_command(t_serv *s);
void						add_token(t_serv *s, t_token *new);
t_token						*init_token(t_serv *s, t_type type, char *str,
							size_t len);
size_t						len_to_end(t_serv *s, char end);
int							get_offset(t_serv *s, t_instr *instr, char *label);
unsigned char arg_coding_byte(t_instr *ptr);
void						print_arg(t_instr *ptr, int i);
void						print_dump(t_serv *s);
void						parse_reg(t_serv *s, int i);
void						parse_ind(t_serv *s, int i);
void						parse_dir(t_serv *s, int i);
void						parse_arg(t_serv *s, int i);
void						parse_arguments(t_serv *s);
void						parse_prog_comment(t_serv *s);
void						parse_prog_name(t_serv *s);
void						parse_label(t_serv *s);
int							parse_op(t_serv *s);
void						parse_string(t_serv *s);
t_op						*get_op(char *name);
void						add_instr(t_serv *s, t_instr *new);
void						print_instr(t_instr *ptr);
int							ft_atoi_base(char *nb, int base);
int							ft_atoi_check(char *nb);
void print_instr_code(t_instr *instr, int pass);
uint32_t					swap_bytes_old(uint32_t num, size_t len);
void						parse_ref_label(t_serv *s);
void						code_labels(t_serv *s);

#endif
