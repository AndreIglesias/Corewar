/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:46:23 by ciglesia          #+#    #+#             */
/*   Updated: 2020/09/27 18:03:24 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include "asm.h"

# define REG					1
# define DIR					2
# define IND					3

typedef struct					s_w
{
	char						*name;
	t_uchar						nb_arg;
	t_arg_type					args[3];
	t_uchar						opcode;
	unsigned int				cycle;
	char						*description;
	t_uchar						octal;
	t_uchar						label;
	void						(*f)(t_file *file, int *pos);
}								t_w;

int								valid_header(t_file *file);

int								load_exec(t_file *file);

int								init_writing(t_file *file);

int								disassemble(t_file *file);
int								octal_shift(t_uchar acb, t_uchar label_size,
											t_uchar narg);
int								reverse_bytes(t_uchar *code, unsigned int pc,
											int bytes);
int								is_argsize(t_uchar ir, t_uchar acb,
											t_uchar narg);
int								p_acb(t_uchar acb, int p_number);
int								is_reg(t_uchar *code, int nb);

void							get_arg(t_uchar *code, int pos, t_uchar *move,
										t_file *file);
void							disect_args(t_uchar *code, int *pos, int l,
											t_file *file);
void							w_live(t_file *file, int *pos);
void							w_ld(t_file *file, int *pos);
void							w_st(t_file *file, int *pos);
void							w_add(t_file *file, int *pos);
void							w_sub(t_file *file, int *pos);
void							w_and(t_file *file, int *pos);
void							w_or(t_file *file, int *pos);
void							w_xor(t_file *file, int *pos);
void							w_zjmp(t_file *file, int *pos);
void							w_ldi(t_file *file, int *pos);
void							w_sti(t_file *file, int *pos);
void							w_fork(t_file *file, int *pos);
void							w_lld(t_file *file, int *pos);
void							w_lldi(t_file *file, int *pos);
void							w_lfork(t_file *file, int *pos);
void							w_aff(t_file *file, int *pos);

extern t_w						g_w_tab[17];

#endif
