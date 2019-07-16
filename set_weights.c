/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/16 10:15:04 by mbartole         ###   ########.fr       */
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
		ultimate_exit(mngr, MALLOC_ERROR);
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
** set weight of /edge/ by weight of its /nodes/
** or 0 for inner edge
*/

static void	set_edge_weight(t_edge *edge)
{
	if (edge->from->wrap == edge->to->wrap)
		edge->wgth = 0;
	else
		edge->wgth = edge->from->counter - edge->to->counter + 1;
}

/*
** set weight of /node/ and push it to queue
*/

static void	*set_node_weight(t_vector *que, t_node *nod, t_node *prev,
		t_mngr *mngr)
{
	nod->counter = nod->wrap == prev->wrap ? prev->counter : prev->counter + 1;
	que = que_add(que, nod, mngr);
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
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->start->counter = 0;
	que = que_add(que, mngr->start, mngr);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter == -1)
				que = set_node_weight(que, EDGE->to, cur, mngr);
			if (EDGE->wgth == -1)
				set_edge_weight(EDGE);
			child = child->next;
		}
		print_node(cur); // TODO remove
	}
	ft_vecdel((void **)&que);
}
