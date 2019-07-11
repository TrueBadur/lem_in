/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/11 18:20:26 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define QUE_SIZE 100 * sizeof(t_node*)

/*
** push one / node* / to queue
** if smth goes wrong, just exit safely
*/

void		*que_add(t_vector *que, t_node *node, t_mngr *mngr)
{
	que = ft_vecpush(que, &node, sizeof(t_node*));
	if (!que)
		ultimate_exit(&mngr);
	return (que);
}

/*
** pop(0) one / node* / from queue
*/

t_node		*que_popleft(t_vector *que)
{
	que->offset += sizeof(t_node*);
	return (((t_node **)que->data)[que->offset / sizeof(t_node*) - 1]);
}

/*
** set weight of /edge/ and /edge->reverse/ by weight of its /nodes/
*/

static void	set_both_edges_weight(t_edge *edge)
{
	edge->wgth = edge->from->counter - edge->to->counter + 1;
	edge->reverse->wgth = edge->to->counter - edge->from->counter + 1;
}

/*
** set weight of /node/ and push it to queue
*/

void		*set_node_weight(t_vector *que, t_node *node, int w, t_mngr *mngr)
{
	node->counter = w;
	que = que_add(que, node, mngr);
	return (que);
}

/*
** set weights to all Nodes and Edges by BreadthFirstSearch of input graph
*/

#define EDGE ((t_edge *)child->data)

void		set_weights(t_mngr *mngr)
{
	t_vector	*que;
	t_node		*cur;
	t_list		*child;

	if (!(que = ft_vecinit(QUE_SIZE)))
		ultimate_exit(&mngr);
	mngr->start->counter = 0;
	que = que_add(que, mngr->start, mngr);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter == -1)
				que = set_node_weight(que, EDGE->to, cur->counter + 1, mngr);
			if (EDGE->wgth == -1)
				set_both_edges_weight(EDGE);
			child = child->next;
		}
		print_node(cur); // TODO remove
	}
	ft_vecdel((void **)&que);
}
