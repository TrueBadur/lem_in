/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/11 18:18:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** deletes all two-direction edges from graph
** (walking it by BFS from finish)
*/

void	clean_graph(t_mngr *mngr, int iter)
{
	t_vector	*que;
	t_node		*cur;
	t_list		*child;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(&mngr);
	mngr->end->counter = iter;
	que = que_add(que, mngr->end, mngr);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter != iter)
				set_node_weight(que, EDGE->to, iter, mngr);
			if (EDGE->reverse)
			{
				del_from_links(&(EDGE->to->links), EDGE->reverse);
//				free(EDGE->reverse); // TODO free
				del_from_links(&(EDGE->from->links), EDGE);
//				free(EDGE); // TODO free
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}

//void		get_aunt(t_vector *que, t_node *cur, t_edge *edge)
//{
//	if (edge->to->counter > 0)
//	{
//		edge->from->counter++;
//		edge->to->counter--;
//		que_add(que, cur);
//	}
//}

/*
** moves aunts towards finish by shortest paths first
*/

//void 		move_lems(t_node *fin)
//{
//	t_vector 	*que;
//	t_node		*cur;
//	t_list		*child;
//
//	que = ft_vecinit(SIZE_OF_QUE);
//	que_add(que, fin);
//	while (que->len != que->offset) {
//		cur = que_popleft(que);
//		child = cur->links;
//		if (cur == fin)
//			while (child) {
//				get_aunt(que, cur, EDGE);
//				child = child->next;
//			}
//		else
//			get_aunt(que, cur, EDGE);
//	}
//	ft_vecdel((void **)&que);
//}

/*
** overall algorithm
*/

void	get_all_paths(t_mngr *mngr)
{
	int i;

	set_weights(mngr);
	printf("weights set\n\n");
	i = suurballe(mngr);
	printf("dijkstra has %i runs\n", -i-1);
	clean_graph(mngr, i - 1);
//	move_lems(fin);
}
