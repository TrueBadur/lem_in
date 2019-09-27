/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/27 19:41:19 by ehugh-be         ###   ########.fr       */
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
//	if (edge->from->wrap == edge->to->wrap)
//		edge->wgth = 0;
//	else
		edge->wgth = edge->from->label < edge->to->label ? 1 : -1;
}

/*
** set weight of /node/ and push it to queue
*/

static void	*set_node_weight(t_vector *que, t_node *nod, t_node *prev,
		t_mngr *mngr)
{
	nod->counter = prev->counter + 1;
	nod->label = nod->counter;
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
	mngr->start->label = 0;
	que = que_add(que, mngr->start, mngr);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter == -1)
				que = set_node_weight(que, EDGE->to, cur, mngr);
//			if (EDGE->wgth == -1)
				set_edge_weight(EDGE);
//ft_printf("{\\13}%p {eof}", EDGE->from);

//			ft_printf("# {Green}|%s - %s (%d - %d - %d) | {eof}",
//					  EDGE->from->wrap->name,
//					  EDGE->to->wrap->name,
//					  EDGE->from->label,
//					  EDGE->wgth,
//					  EDGE->to->label);
			child = child->next;
		}
//		ft_printf("\n");
	}
//	t_wnode* tmp = ft_avlsearch(mngr->all_rooms, "Vlj6", 1, NULL);
//	print_node(&tmp->in);
//	print_node(&tmp->out);
	ft_vecdel((void **)&que);
}

static void	*reset_node_weight(t_vector *que, t_node *nod, t_node *prev,
								t_mngr *mngr)
{

	return (que);
}

void set_potentials(t_vector *all_nodes)
{
	int len;
	int i;
	t_wnode **nodes;
	t_node *tmp;

	len = (int) (all_nodes->len / sizeof(void *));
	nodes = (t_wnode **)all_nodes->data;
	i = -1;
	while (++i < len)
	{
		nodes[i]->in.label += nodes[i]->in.path_priority.x;
		nodes[i]->out.label += nodes[i]->out.path_priority.x;
		nodes[i]->in.path_priority = (t_int2){INT32_MAX, INT32_MAX};
		nodes[i]->out.path_priority = (t_int2){INT32_MAX, INT32_MAX};
//		ft_printf("%p ", nodes[i]);
//		ft_printf("#{\\54} (%d - %d: %s) {eof}", nodes[i]->in.label,
//				nodes[i]->out.label, nodes[i]->name);
	}
}