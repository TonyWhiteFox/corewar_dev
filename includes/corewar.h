/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:51:18 by lshellie          #+#    #+#             */
/*   Updated: 2020/06/21 17:25:04 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COREWAR_H
# define _COREWAR_H
# include "libft.h"
# include <mlx.h>
# include "op.h"
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define AFF_OP 1
# define LLD_READ_SIZE 2
# define LIVE 1
# define LD 2
# define ST 3
# define ADD 4
# define SUB 5
# define AND 6
# define OR 7
# define XOR 8
# define ZJMP 9
# define LDI 10
# define STI 11
# define FORK 12
# define LLD 13
# define LLDI 14
# define LFORK 15
# define AFF 16

# define MAX_OPS 16

# define DIR 1
# define REG 2
# define IND 3

# define NUM_ARG 0
# define T_DIR_SIZE 5
# define PRICE 6

typedef struct			s_opencl //new
{
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_context			context;
	cl_mem				mem_picture;
	cl_mem				mem_map;
	cl_mem				mem_log;
	cl_mem				mem_serf;
	cl_mem				mem_live;
	cl_mem				mem_decor;
	cl_command_queue	command_queue;
	int					ret;
	cl_int				*ret_pic;
	cl_int				flows;
	bool				*decor;
	char				*file;
	size_t				win_size;
	size_t				kernel_size;
}						t_opencl;

typedef struct			s_mlx //new
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	void				*img_adr; //send to cl 0
	int					bpp;
	int					stride;
	int					endian;
	int					cycle_per_frame;
	int					sleep_after_frame;
	bool				stop;
}						t_mlx;

typedef struct			s_serf
{
	int					*reg;
	long unsigned int	id;
	int					pos;
	bool				jump;
	int					spell;
	int					left_to_cust;
	int					last_live_cycle;
	short int			creater_no;
	struct s_serf		*next;
}						t_serf;

typedef struct			s_gamer
{
	int					num;
	char				*name;
	char				*comment;
	int					size;
	char				*code;
	struct s_gamer		*next;
}						t_gamer;

typedef struct			s_option
{
	int					total_len;
	int					*var_type;
	int					*var_len;
	int					*variable;
}						t_option;

typedef struct			s_virt
{
//lists
	t_gamer				*gamer;
	t_serf				*serf;
//struct
	t_mlx				*mlx;
	t_opencl			*opencl;
	t_option			*option;
//arrays
	cl_uchar			*map;
	cl_uint				*log;
	bool				*have_serf;
	cl_int				*live_log;
//used in general cycle
	long unsigned int	last_serf_id;
	int					total_gamers;
	short				w_x;
	short				w_y;
	int					total_cycles;
	int					cycles;
	int					life_in_die_cycle;
	int					cycles_before_die;
	short				without_abbreviations;
	int					player_num_last_say_life;
//free after read players
	cl_int				temp;
	int					fd;
//flags
	int					d;
	int					dump;
	int					number;
	bool				vis;
	bool				hardcore;
}						t_virt;

#endif
