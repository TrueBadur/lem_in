/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 05:21:55 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000
#define EDGE ((t_edge *)child->data)

/*
** one run of Dijkstra algorithm trough graph,
** it sets /path/ field of /node/ from start up to finish
** and /counter/ field of /node/ to /iter/
*/

int	dijkstra(t_node *start, t_node *fin, int iter)
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
				if (to == fin) {
					ft_vecdel((void **)&queue);
					return (0);
				}
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&queue);
	return (-1);
}

/*
** delete one link from /node/->/links/
*/

void		del_from_links(t_list **links, t_edge *one)
{
	t_list *tmp;
	t_list *del;

	tmp = *links;
	while (tmp->next->data != one)
		tmp = tmp->next;
	del = tmp->next;
	tmp->next = del->next;
	free(del);
}

#define NEG_WEIGHT -10

/*
** go by /path/s from finish to start,
** reverse or/and delete edges, switch weights
*/

void	reverse_path(t_node *fin)
{
	t_edge	*edge;
	t_node	*from;
	t_node	*to;

	edge = fin->path;
	from = fin;
	while (edge)
	{
		if (from == edge->node1)
		{
			to = edge->node2;
			if (edge->wgth21 == NEG_WEIGHT)
				del_from_links(&from->links, edge);
			else {
				edge->wgth12 = edge->wgth21;
				edge->wgth21 = NEG_WEIGHT;
			}
		}
		else
		{
			to = edge->node1;
			if (edge->wgth12 == NEG_WEIGHT)
				del_from_links(&from->links, edge);
			else {
				edge->wgth21 = edge->wgth12;
				edge->wgth12 = NEG_WEIGHT;
			}
		}
		del_from_links(&to->links, edge);
		from = to;
		edge = to->path;
	}
}

#define MIN(x, y) (x < y ? x : y)

int	suurballe(t_node *start, t_node *fin)
{
	int 	iter;
	int 	limit;

	iter = -1;
	limit = -MIN(ft_lstlen(start->links), ft_lstlen(fin->links)) - 1;
	while (iter > limit)
	{
		--iter;
		if (dijkstra(start, fin, iter))
			break ;
		reverse_path(fin);
	}
	return (iter);
}
