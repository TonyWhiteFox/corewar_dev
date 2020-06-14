/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:51:18 by lshellie          #+#    #+#             */
/*   Updated: 2020/06/14 22:14:42 by ldonnor-         ###   ########.fr       */
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

# define GET_COMMENT 0
# define GET_NAME 1

# define NO_ARG "No arguments"
# define BAD_FLAG "Wrong -n flag"
# define BAD_FILE_FORMAT "Bad format"
# define CANT_OPEN_FILE "Can't open file"
# define WRONG_NUM "Bad num of players"
# define BAD_HEADER "Bad header"
# define READ_ERROR "Read error"
# define INVALID_MALLOC "Malloc error"
# define NO_NULL "No null bytes"
# define INV_CHAP_SIZE "Too big champion"

# define AFF_OP 1
# define LLD_READ_SIZE 2
# define DUMP_LEN 64
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
# define TYPE_BYTE 1
# define ARG1 2
# define ARG2 3
# define ARG3 4
# define T_DIR_SIZE 5
# define PRICE 6

typedef struct			s_cursor
{
	int					id;
	// short int			creater_no; //new
	int					pos;
	int					carry;
	int					op;
	int					last_live_cycle;
	int					action;
	int					*reg;
	struct s_cursor		*next;
}						t_cursor;

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
	cl_mem				mem_field;
	cl_mem				mem_changers;
	cl_mem				mem_cursor;
	cl_mem				mem_live;
	cl_mem				mem_decor;
	cl_command_queue	command_queue;
	int					ret;
	cl_int				*ret_pic;
	cl_uchar			*send_field;
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

typedef struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					size;
	char				*code;
	struct s_player		*next;
}						t_player;

typedef struct			s_main
{
	t_player			*player;
	t_cursor			*cursor;
	t_mlx				*mlx;//new
	t_opencl			*opencl;//new
	short				w_x;//new
	short				w_y;//new
	int					cursor_ids;
	int					dump;
	int					n_flag;
	cl_uchar			*field; //send to cl 1
	cl_int				*changes; //new //send to cl 2
	bool				*have_cursor; //new //send to cl 3
	cl_int				*live; //new //send to cl 4
	int					num_of_players;
	int					last_player_live;
	int					live_num;
	int					check_num;
	int					cycle;
	int					total_cycle;
	int					cycles_to_die;
	bool				v_flag;
}						t_main;

typedef struct			s_o
{
	int					*t;
	int					step;
	int					*s;
	int					*x;
}						t_o;

int						set_player_fl(t_main *m, t_player *new);
int						set_player(t_main *m, t_player *new);
void					swap_players(t_player *a, t_player *b);
int						ft_error(char *str);
void					free_main(t_main *main);
int						is_number(char *str);
void					free_cursor(t_main *main);
int						read_files(t_main *m, int ac, char **av, int i);
int						manage_n(t_main *m, int ac, char **av);
int						get_header(int fd);
int						get_null(int fd);
int						get_name_or_comment(t_player *player, int fd, int fl);
int						get_size(t_player *player, int fd);
int						get_code(t_player *player, int fd);
int						start_game(t_main *main);
void					set_cursor(t_cursor **first, t_cursor *cursor);
t_cursor				*new_cursor();
int						dump_memory(char *field);
void					*free_o(t_o *o);

int						check(t_main *main);
int						check_cursors(t_main *m);
void					check_cursors_while(t_main *m, t_cursor *c,
											t_cursor *prev);

int						start_fight(t_main *main);
void					do_op(t_main *m, t_cursor *c);
int						c_p(int pos);
int						s(int t, int op);
t_o						*manage_type(t_main *m, t_cursor *c);
void					get_args(t_main *m, t_cursor *c, t_o *o);
void					do_live(t_main *m, t_cursor *c);
void					do_zjmp(t_main *m, t_cursor *c);
void					do_fork(t_main *m, t_cursor *c);
void					set_mem(t_main *m, int reg,
								int copy_in_pos, int copy_of_pos);
int						read_mem(char *f, int pos, int size);
void					modify_carry(t_cursor *c, int reg);
void					get_reg(t_cursor *c, t_o *o);
t_player				*choose_player(t_main *m);
void					do_ld(t_main *m, t_cursor *c, t_o *o);
void					do_add_sub(t_main *m, t_cursor *c, t_o *o);
void					do_sti(t_main *m, t_cursor *c, t_o *o);
void					do_st(t_main *m, t_cursor *c, t_o *o);
void					do_ldi(t_main *m, t_cursor *c, t_o *o);
void					do_aff(t_main *m, t_cursor *c, t_o *o);
void					do_and_or_xor(t_main *m, t_cursor *c, t_o *o);
int						choose_type(char tmp);
int						is_player_num(int i, t_player *p);

bool					find_dump_vis_flags(t_main *m, int ac, char **av,
											int *i);
void					init_visualisation(t_main *m);


void					start_fight_mlx_hooks(t_main *m);
int						mouse_move_hook(int x, int y, t_main *m);
int						key_press(int key, t_main *m);
int						say_good_buy(t_main *m);
int						mouse_click_hook(int k, int x, int y, t_main *m);
void					fill_decor_bool_array(t_opencl *o);

#endif
