/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/09 20:44:30 by mbartole         ###   ########.fr       */
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

/*
** bfs.c
*/

void			que_add(t_vector *que, t_node *node);
t_node			*que_popleft(t_vector *que);
void			set_node_weight(t_vector *que, t_node *node, int weight);
void 			set_weights(t_node *root);

void			del_from_links(t_list **links, t_edge *one);
int				suurballe(t_node *start, t_node *fin);

void			clean_graph(t_node *fin, int iter);
void			get_all_paths(t_node *start, t_node *fin, int n);

void	my_test(void);
void	print_edge(t_edge *edge);
void	print_node(t_node *node);
void	print_gr();

#endif
