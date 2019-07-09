/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/09 19:18:24 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include "libft.h"
//# include "pque.h"
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

typedef struct	s_mngr
{
	int			flags; //TODO convert to more flags or to bitarray
	unsigned	ant_num;
	t_btavl		*all_rooms;
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

typedef enum 	e_errors
{
	INPUT_ERROR
}				t_err;

void	*parse_flags(int argc, char **argv, t_mngr *mngr);

void	parse_input(t_mngr *mngr);
t_elt	check_line_type(char *line);
t_elt	get_room(t_mngr *mngr, char *line);
t_elt	get_link(t_mngr *mngr, char *line);

t_mngr	*init_mngr(void);
void	make_magic(t_mngr *mngr);
void	print_solution(t_mngr *mngr);
void	ultimate_exit(t_mngr **mngr);

void			que_add(t_vector *que, t_node *node);
t_node			*que_popleft(t_vector *que);
void			set_node_weight(t_vector *que, t_node *node, int weight);
void 			bfs(t_node *root);

void			del_from_links(t_list **links, t_edge *one);
int				suurballe(t_node *start, t_node *fin);

void			clean_graph(t_node *fin, int iter);

#endif
