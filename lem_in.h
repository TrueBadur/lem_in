/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/08 05:21:55 by mbartole         ###   ########.fr       */
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
	struct s_node	*node1;
	struct s_node	*node2;
	int 			wgth12;  // -1 by default
	int 			wgth21;  // -1 by default
}				t_edge;

typedef struct s_node
{
	int			counter; // -1 by default
	t_edge		*path;  // NULL by default
	char		*name;
	t_list		*links;  // t_edge
}				t_node;

void			que_add(t_vector *que, t_node *node);
t_node			*que_popleft(t_vector *que);
void 			bfs(t_node *root);

void			del_from_links(t_list **links, t_edge *one);
int				suurballe(t_node *start, t_node *fin);

void			clean_graph(t_node *fin, int iter);

#endif
