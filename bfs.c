/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/07 17:02:07 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define QUE_SIZE 1000

/*
** add Node to queue
*/

static void		que_add(t_vector *que, t_node *node)
{
	ft_vecpush(que, node, sizeof(t_node*));
}

/*
** pop(0) one Node from queue
*/

static t_node	*que_popleft(t_vector *que)
{
	que->offset += sizeof(t_node*);
	return (((t_node **)que)[0]);
}

/*
** set weight of Edge by weight of its Nodes
*/

static void		set_edge_weight(t_edge *edge)
{
	edge->wgth = edge->from - edge->to + 1;
}

/*
** set weights to all Nodes and Edges by BreadthFirstSearch of input graph
*/

void	bfs(t_node *root)
{
	t_vector	*que;
	t_node		*cur;
	t_list		*child;

	que = ft_vecinit(sizeof(t_node*) * QUE_SIZE);
	root->wgth = 0;
	que_add(que, root);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (((t_edge *)child->data)->to->wgth == -1)
			{
				((t_edge *)child->data)->to->wgth = cur->wgth + 1;
				que_add(que, ((t_edge *) child->data)->to);
			}
			set_edge_weight((t_edge *)child->data);
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}