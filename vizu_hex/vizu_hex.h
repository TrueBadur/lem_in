/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizu_hex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:59:54 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/12 16:55:37 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VIZU_HEX_H
# define LEM_IN_VIZU_HEX_H

# include "libft.h"
# include <mlx.h>
#include "mlx_helper.h"
#include <lem_in.h>

#define START_NODES 16
#define VNODE(x) ((t_viznode *)(x))

/* STRUCTURES */

typedef struct	s_viznode
{
	char				*name;
	struct s_viznode	*children;
	t_img				img;
	t_ucol4				col;
}				t_viznode;

typedef struct	s_ant
{
	int			name; //maybe it wouldn't be usefull
	t_ucol4		color;
	t_viznode	room;
}				t_ant;

typedef struct	s_mngr
{
	int			ant_num;
	t_mlx		*mlx;
	t_vector	*ants;
	t_vector	*nodes;
	t_instr		instr;
	t_viznode	*start;
	t_viznode	*end;

}				t_mngr;

/* FUNCTIONS */

void	vh_parse_input(t_mngr * mngr);
t_elt check_line_type(char *line, int viz);

#endif //LEM_IN_VIZU_HEX_H
