/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 18:51:15 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define QUE_SIZE 1000 * sizeof(t_node)

/*
** push one /node/ to queue
*/

void			que_add(t_vector *que, t_node *node)
{
	ft_vecpush(que, node, sizeof(t_node*));
}

/*
** pop(0) one /node/ from queue
*/

t_node			*que_popleft(t_vector *que)
{
	que->offset += sizeof(t_node*);
	return (((t_node **)que)[0]);
}

/*
** set weight of /edge/ and /edge->reverse/ by weight of its /nodes/
*/

static void		set_both_edges_weight(t_edge *edge)
{
	edge->wgth = edge->from->counter - edge->to->counter + 1;
	edge->reverse->wgth = edge->to->counter - edge->from->counter + 1;
}

/*
** set weight of /node/ and push it to queue
*/

void			set_node_weight(t_vector *que, t_node *node, int weight)
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
	t_list		*child;

	que = ft_vecinit(QUE_SIZE);
	root->counter = 0;
	que_add(que, root);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter == -1)
				set_node_weight(que, EDGE->to, cur->counter + 1);
			if (EDGE->wgth == -1)
				set_both_edges_weight(EDGE);
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}
