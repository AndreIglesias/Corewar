/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 22:51:24 by ciglesia          #+#    #+#             */
/*   Updated: 2020/08/25 17:59:01 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"

typedef struct		s_vm
{
	t_list			*process_lst;
	t_arena			a;
	t_player		p[MAX_PLAYERS];
	int				nplayer;
	int				nprocess;
	int				nprocess_alive;
	int				last_live_id;
	int				ncycle;
	int				ncycle_mod;
	int				nlive_bctd;
	int				cycle_to_die;
	int				ncheck;
	int				is_ctd_modified;
	int				display_mode;
	t_viewer		*v;
	unsigned int	opt_flags;
	int				dump_param;
	int				nplayer_cust;
	int				verbose_param;
}					t_vm;

#endif
