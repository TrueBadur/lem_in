/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 18:34:28 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** one run of Dijkstra algorithm trough graph,
** it sets /path/ field of /node/ from start up to finish
** and sets /counter/ field of /node/ to /iter/ (markdown of walk)
*/

int	dijkstra(t_node *start, t_node *fin, int iter)
{
	t_vector 	*que;
	t_pque		cur;
	t_list		*child;

	que = ft_vecinit(SIZE_OF_QUE);
	push_que(que, start, 0);
	start->counter = iter;
	start->path = NULL;
	while (que->len > 0)
	{
		cur = pop_que(que);
		child = ((t_node *)cur.data)->links;
		while (child)
		{
			if (EDGE->to->counter != iter)
			{
				EDGE->to->counter = iter;
				EDGE->to->path = EDGE;
				if (EDGE->to == fin)
				{
					ft_vecdel((void **)&que);
					return (0);
				}
				push_que(que, EDGE->to, cur.priority + EDGE->wgth);
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
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

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights
*/

void	reverse_path(t_node *fin)
{
	t_edge	*edge;
	t_node	*next;

	edge = fin->path;
	while (edge)
	{
		next = edge->from;
		if (edge->reverse)
		{
			edge->reverse->wgth = edge->wgth;
			edge->reverse->reverse = NULL;
		}
		free(edge);
		del_from_links(&edge->from->links, edge);
		edge = next->path;
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
