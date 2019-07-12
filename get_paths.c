/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/12 17:21:11 by mbartole         ###   ########.fr       */
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
		ultimate_exit(mngr, MALLOC_ERROR);
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
				del_edge(&(EDGE->to->links), EDGE->reverse);
				del_edge(&(EDGE->from->links), EDGE);
			}
			child = child->next;
		}
	}
	ft_vecdel((void **)&que);
}

//void		get_ant(t_vector *que, t_node *cur, t_edge *edge)
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

//void		calc_aunts(int *ants, int n)
//{
//
//}

t_vector	*get_output(t_mngr *mngr, int size)
{
	t_vector	*output;
	int			ants[size];
	t_node		*ends[size];
	t_list		*cur;
	int 		i;

	i = 0;
	cur = mngr->end->links;
	while (cur)
	{
		ends[i] = ((t_edge*)cur->data)->to;
		ants[i] = 1;
		while (1)
		{
			ants[i]++;
			if (((t_edge *)ends[i]->links->data)->to == mngr->start)
				break ;
			ends[i] = ((t_edge *)ends[i]->links->data)->to;
		}
		printf("len = %i     ", ants[i]); // TODO remove
		print_node(ends[i]);  // TODO remove
		cur = cur->next;
		i++;
	}
//	calc_aunts(ants, mngr->ant_num);
	if (!(output = ft_vecinit(10 * mngr->ant_num * sizeof(char))))
		ultimate_exit(mngr, MALLOC_ERROR);
	return (output);
}

/*
** overall algorithm
*/

void		get_all_paths(t_mngr *mngr)
{
	int			i;
	t_vector	*output;

	set_weights(mngr);
	printf("weights set\n\n"); // TODO remove
	if ((i = suurballe(mngr)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
	printf("dijkstra has %i runs\n", -i - 2);  // TODO remove
	clean_graph(mngr, i - 1);
	output = get_output(mngr, ft_lstlen(mngr->end->links));
	ft_printf("%s", (char*)output->data);
	ft_vecdel((void **)&output);
}
