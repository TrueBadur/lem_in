/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/08 05:22:01 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define NEG_WEIGHT -10
#define SIZE_OF_QUE 1000
#define EDGE ((t_edge *)child->data)


void	clean_graph(t_node *fin, int iter)
{
	t_vector	*que;
	t_node		*cur;
	t_node		*next;
	t_list		*child;

	que = ft_vecinit(sizeof(t_node*) * SIZE_OF_QUE);
	fin->counter = iter;
	que_add(que, fin);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			next = NULL;
			if (EDGE->node1->counter != iter)
				next = EDGE->node1;
			if (EDGE->node2->counter != iter)
				next = EDGE->node2;
			if (next)
			{
				if (EDGE->wgth12 == NEG_WEIGHT || EDGE->wgth21 == NEG_WEIGHT) {
					del_from_links(&(EDGE->node1->links), EDGE);
					del_from_links(&(EDGE->node2->links), EDGE);
					free(EDGE);
				}
				next->counter = iter;
				que_add(que, next);
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}

void 	move_lems(t_node *fin)
{

}

void	get_all_paths(t_node *start, t_node *fin)
{
	int i;

	bfs(start);
	i = suurballe(start, fin);
	clean_graph(fin, i - 1);
}
