/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/24 17:45:42 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include "libft.h"
# include "pque.h"
#include <stdio.h> // TODO: delete

struct s_node;
struct s_wnode;

typedef struct	s_edge
{
	struct s_node	*from;
	struct s_node	*to;
	int 			wgth;  // -1 by default
	char			was_rev; // 0 by default
}				t_edge;

typedef struct s_node
{
	int				counter; // -1 by default
	t_edge			*path;  // NULL by default
	struct s_wnode	*wrap;
	t_list			*links;  // t_edge
}				t_node;

typedef struct s_wnode
{
	char 	*name;
	t_node	in;
	t_node	out;
}				t_wnode;

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
void 			set_weights(t_mngr *mngr);

int				suurballe(t_mngr *mngr, t_list **ends);

void			do_all_job(t_mngr *mngr);

t_list			*pop_edge(t_list **links, t_edge *one);
void			swap_nodes(t_node **a, t_node **b);
int				get_path_len(t_node *node, t_node *start, char to_relink,
								t_node **to_set);
int			set_path_len(t_node *node, t_node *start, char to_relink, t_node **to_set);
int				calc_len_of_output(t_list *ends, int size, int ants,
									t_node *start);

void			calc_ants(t_mngr *mngr, int size, t_node **ends);
int				get_one_line(int **params, t_vector **output, t_mngr *mngr,
								int *cur_lem);



void	print_edge(t_edge *edge);
void	print_node(t_node *node);
void	test(t_mngr *mngr);

#endif
