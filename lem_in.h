/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/11 18:18:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include "libft.h"
# include "pque.h"
#include <stdio.h> // TODO: delete

struct s_node;

typedef struct	s_edge
{
	struct s_node	*from;
	struct s_node	*to;
	int 			wgth;  // -1 by default
	struct s_edge	*reverse;  // NULL by default
}				t_edge;

typedef struct s_node
{
	int			counter; // -1 by default
	t_edge		*path;  // NULL by default
	char		*name;
	t_list		*links;  // t_edge
}				t_node;

typedef enum	e_instuctions
{
	INSTR_NONE,
	START,
	FINISH
}				t_instr;


typedef enum	e_line_types
{
	LT_NONE = -1,
	ANT_N,
	ROOM,
	LINK,
	COMMENT,
	INSTRUCTION,
	ERROR
}				t_elt;


typedef enum 	e_errors
{
	SUCCESS,
	MALLOC_ERROR,
	NOT_ENOUGH_DATA,
	NO_PATHS_FOUND,
}				t_err;

typedef struct	s_mngr
{
	int			flags; //TODO convert to more flags or to bitarray
	int			ant_num;
	t_btavl		*all_rooms;
	t_instr		instr;
	t_node		*start;
	t_node		*end;
	t_elt		max_lt;
}				t_mngr;

void	*parse_flags(int argc, char **argv, t_mngr *mngr);

void	parse_input(t_mngr *mngr);
t_elt	check_line_type(char *line);
t_elt	get_room(t_mngr *mngr, char *line);
t_elt	get_link(t_mngr *mngr, char *line);

void	make_magic(t_mngr *mngr);
void	print_solution(t_mngr *mngr);
void ultimate_exit(t_mngr *mngr, int exit_code);

void			*que_add(t_vector *que, t_node *node, t_mngr *mngr);
t_node			*que_popleft(t_vector *que);
void			*set_node_weight(t_vector *que, t_node *node, int w, t_mngr *mngr);
void 			set_weights(t_mngr *mngr);

void			del_edge(t_list **links, t_edge *one);
int				suurballe(t_mngr *mngr);

void			clean_graph(t_mngr *mngr, int iter);
void			get_all_paths(t_mngr *mngr);


void	print_edge(t_edge *edge);
void	print_node(t_node *node);

#endif
