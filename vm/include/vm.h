/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 21:50:15 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/12 21:33:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>
# include "libft.h"
# include "op.h"

# define MAX_SPEED	0
# define MIN_SPEED	30000

# define TP			t_process
# define P			process

/*
**# define ACB1		(acb & 0b11000000) >> 6	-> p_acb()
**# define ACB2		(acb & 0b110000) >> 4	-> p_acb()
**# define ACB3		(acb & 0b1100) >> 2		-> p_acb()
**# define REG		0b01
**# define DIR		0b10
**# define IND		0b11
*/

# define REG		1
# define DIR		2
# define IND		3

typedef struct		s_matrix
{
	int				row;
	int				col;
	int				i;
}					t_matrix;

typedef struct		s_arena
{
	t_uchar			arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	char			scrb[MEM_SIZE];
}					t_arena;

typedef struct		s_process
{
	int				nprocess;
	int				carry;
	int				reg[REG_NUMBER];
	int				pc;
	int				duration;
	int				live_count;
	int				live_since;
	int				owner;
	t_uchar			ir;
	t_uchar			last_ir;
	t_uchar			optab;
}					t_process;

typedef struct		s_player
{
	int				nplayer;
	t_uchar			name[PROG_NAME_LENGTH + 1];
	t_uchar			comment[COMMENT_LENGTH + 1];
	t_uchar			code[CHAMP_MAX_SIZE];
	int				prog_size;
	int				exec_magic;
	int				pc_address;
	int				nblive;
	int				last_live_cycle;
	struct s_player	*next;
}					t_player;

typedef struct		s_vm
{
	t_arena			ram;
	t_list			*processes;
	t_player		*player;
	int				dump_param;
	int				nplayers;
	int				last_alive;
	int				nprocess;
	int				process_alive;
	int				cycle_to_die;
	int				cycles;
	int				nchecks;
	int				nlives;
	int				ncurses;
	int				speed;
	WINDOW			*m_win;
	int				height;
	int				width;
	WINDOW			*s_win;
	int				s_width;
	WINDOW			*p_win;
	int				p_height;
	int				proc_y;
	int				pause;
}					t_vm;

typedef struct		s_param
{
	int				dump;
	t_list			*players;
}					t_param;

/*
** loading
*/

int					vm_load(t_vm *vm, int ac, char **av);
int					load_input(t_vm *vm, int ac, char **av);
int					load_champions(t_vm *vm);
int					load_processes(t_vm *vm, t_player *champion, int i);
void				add_player(t_vm *vm, t_player *new);
t_player			*new_player();
int					add_process(t_vm *vm, t_list *process, unsigned int pc);
void				kill_players(t_vm *vm);

/*
** validation
*/

int					valid_input(int ac, char **av);
int					is_dump(int i, int ac, char **av);
int					is_champion(int i, int ac, char **av, int *np);
int					valid_header(int fd, char *file);

/*
** computer-system
*/

int					vm_init(t_vm *vm);
int					run_processes(t_vm *vm);
int					print_ram(t_vm *vm);
int					is_ir(t_list *process, int i);
int					is_pc(t_list *process, int i);

/*
** op
*/

void				and_op(t_list *process, int *nb, t_vm *vm);
void				or_op(t_list *process, int *nb, t_vm *vm);
void				xor_op(t_list *process, int *nb, t_vm *vm);
void				ldi_op(t_list *process, int *nb, t_vm *vm);
void				lldi_op(t_list *process, int *nb, t_vm *vm);

/*
** parsing: direct_args
*/

int					p_acb(t_uchar acb, int p_number);
void				disect_args(t_vm *vm, t_list *process, int isld,
						void (*f)(t_list *process, int *nb, t_vm *vm));
/*
** parsing
*/

int					is_argsize(t_uchar ir, t_uchar acb, t_uchar narg);
int					reverse_bytes(t_vm *vm, unsigned int pc, int bytes);
int					octal_shift(t_uchar n, t_uchar label_size, t_uchar narg);
void				store_at(t_vm *vm, t_list *process,
					unsigned int val, int address);
int					get_arg(t_vm *vm, t_list *process, t_uchar *move,
							t_uchar type);
void				player_alive(t_vm *vm, int live);
int					is_reg(t_vm *vm, int nb);
unsigned int		mem_mod(int x);
int					in_mem(t_vm *vm, int pc);
void				save_cmp(t_list *process, int id, int comp);
/*
** interface
*/
int					print_arena(t_vm *vm);
int					ncupdate(t_vm *vm, int input);
void				print_panel(WINDOW *win, t_list *process, t_vm *vm);
void				resize_window(t_vm *vm);
void				fill_arena(int height, t_vm *vm, t_matrix m,
								WINDOW *win);

#endif
