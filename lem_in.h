/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/07 21:43:37 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include "libft.h"

struct s_node;

typedef struct	s_edge
{
	int				wgth;
	struct s_node	*from;
	struct s_node	*to;
}				t_edge;

typedef struct s_node
{
	int			wgth;
	char		*name;
	t_edge		**links;
}				t_node;

typedef struct	s_mngr
{
	int			flags; //TODO convert to more flags or to bitarray
	unsigned	ant_num;
}				t_mngr;

typedef enum	e_line_types
{
	COMMENT,
	INSTRUCTION,
	ANT_N,
	ROOM,
	LINK,
	ERROR
}				t_elt;

void	*parse_flags(int argc, char **argv, t_mngr *mngr);

void	parse_input(t_mngr *mngr);
t_elt	check_line_type(char *line);

t_mngr	*init_mngr(void);
void	make_magic(t_mngr *mngr);
void	print_solution(t_mngr *mngr);
void	ultimate_exit(t_mngr *mngr);

#endif //LEM_IN_LEM_IN_H
