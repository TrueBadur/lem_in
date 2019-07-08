/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 05:03:48 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define QUE_SIZE 1000

/*
** add Node to queue
*/

void			que_add(t_vector *que, t_node *node)
{
	ft_vecpush(que, node, sizeof(t_node*));
}

/*
** pop(0) one Node from queue
*/

t_node			*que_popleft(t_vector *que)
{
	que->offset += sizeof(t_node*);
	return (((t_node **)que)[0]);
}

/*
** set weight of Edge by weight of its Nodes
*/

static void		set_edge_weight(t_edge *edge)
{
	edge->wgth12 = edge->node1->counter - edge->node2->counter + 1;
	edge->wgth21 = edge->node2->counter - edge->node1->counter + 1;
}

static void		set_node_weight(t_vector *que, t_node *node, int weight)
{
	node->counter = weight;
	que_add(que, node);
}

/*
** set weights to all Nodes and Edges by BreadthFirstSearch of input graph
*/

#define EDGE ((t_edge *)child->data)

void	bfs(t_node *root)
{
	t_vector	*que;
	t_node		*cur;
	t_node		*next;
	t_list		*child;

	que = ft_vecinit(sizeof(t_node*) * QUE_SIZE);
	root->counter = 0;
	que_add(que, root);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->wgth12 == -1)
			{
				next = EDGE->node1->counter == -1 ? EDGE->node1 : EDGE->node2;
				set_node_weight(que, next, cur->counter + 1);
				set_edge_weight(EDGE);
				que_add(que, next);
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}