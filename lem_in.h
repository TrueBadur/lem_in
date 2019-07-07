/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/07 18:13:31 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# include "libft.h"

struct s_node;

typedef struct	s_edge
{
	struct s_node	*node1;
	struct s_node	*node2;
	int 			wgth12;
	int 			wgth21;
}				t_edge;

typedef struct s_node
{
	int			wgth;
	char		*name;
	t_list		*links;  // t_edge
}				t_node;


void 			bfs(t_node *root);

#endif
