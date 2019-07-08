/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 03:03:50 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000
#define EDGE ((t_edge *)child->data)

void	dijkstra(t_node *start, t_node *fin, int iter)
{
	t_vector 	*queue;
	t_pque		cur;
	t_list		*child;
	t_node		*to;
	int 		w;

	queue = ft_vecinit(SIZE_OF_QUE * sizeof(t_pque));
	push_que(queue, start, 0);
	start->counter = iter;
	start->path = NULL;
	while (queue->len > 0) {
		cur = pop_que(queue);
		child = ((t_node *) cur.data)->links;
		while (child)
		{
			to = (t_node *)cur.data == EDGE->node1 ? EDGE->node2 : EDGE->node1;
			w = (t_node *)cur.data == EDGE->node1 ? EDGE->wgth12 : EDGE->wgth21;
			if (to->counter != iter)
			{
				to->counter = iter;
				to->path = EDGE;
				push_que(queue, to, cur.priority + w);
				if (to == fin)
					return;
			}
			child = child->next;
		}
	}
}

void	reverse_path(t_node *fin)
{
	t_edge	*next;
	t_node	*from;
	t_node	*to;

	next = fin->path;
	from = fin;
	while (next)
	{
		to = from == next->node1 ? next->node2 : next->node1;

		from = to;
		next = to->path;
	}
}