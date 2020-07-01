/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/03/01 16:34:37 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define ALT_COMMENT_CHAR		';'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','
#define WHITESPACE_CHARS			" \t\v\f\r"

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;


/*
** Operator
*/

/*
** name            — name of operator
** code            — code of operator
** args_num        — number of arguments
** args_types_code — does bytecode of statement with this operator contain code
**                   of argument's types
** args_types      — types of arguments
** t_dir_size      — size of T_DIR argument
*/

typedef struct	s_op
{
	char		*name;
	uint8_t		code;
	uint8_t		args_num;
	uint8_t 	args_types_code;
	uint8_t		args_types[3];
	uint8_t		t_dir_size;
}				t_op;

/*
** Array
*/

static t_op		g_op[16] = {
		{
				.name = "live",
				.code = 0x01,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 4,
		},
		{
				.name = "ld",
				.code = 0x02,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
		},
		{
				.name = "st",
				.code = 0x03,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_IND, 0},
				.t_dir_size = 4,
		},
		{
				.name = "add",
				.code = 0x04,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "sub",
				.code = 0x05,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "and",
				.code = 0x06,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "or",
				.code = 0x07,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "xor",
				.code = 0x08,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
				.t_dir_size = 4,
		},
		{
				.name = "zjmp",
				.code = 0x09,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "ldi",
				.code = 0x0A,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
		},
		{
				.name = "sti",
				.code = 0x0B,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
				.t_dir_size = 2,
		},
		{
				.name = "fork",
				.code = 0x0C,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "lld",
				.code = 0x0D,
				.args_num = 2,
				.args_types_code = 1,
				.args_types = {T_DIR | T_IND, T_REG, 0},
				.t_dir_size = 4,
		},
		{
				.name = "lldi",
				.code = 0x0E,
				.args_num = 3,
				.args_types_code = 1,
				.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
				.t_dir_size = 2,
		},
		{
				.name = "lfork",
				.code = 0x0F,
				.args_num = 1,
				.args_types_code = 0,
				.args_types = {T_DIR, 0, 0},
				.t_dir_size = 2,
		},
		{
				.name = "aff",
				.code = 0x10,
				.args_num = 1,
				.args_types_code = 1,
				.args_types = {T_REG, 0, 0},
				.t_dir_size = 4,
		}
};

#endif