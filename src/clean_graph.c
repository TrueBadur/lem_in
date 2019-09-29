/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/29 12:40:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** push one / node* / to queue
** if smth goes wrong, just exit safely
*/

static void		*que_add(t_vector *que, t_node *node, t_mngr *mngr)
{
	que = ft_vecpush(que, &node, sizeof(t_node*));
	if (!que)
		ultimate_exit(mngr, MALLOC_ERROR);
	return (que);
}

/*
** pop(0) one / node* / from queue
*/

static t_node	*que_popleft(t_vector *que)
{
	que->offset += sizeof(t_node*);
	return (((t_node **)que->data)[que->offset / sizeof(t_node*) - 1]);
}

/*
** deletes all not /was_rev/ edges from graph
** (walking it by BFS from finish)
*/

void			clean_graph(t_mngr *mngr, int iter)
{
	t_vector	*que;
	t_list		*child;
	t_list		*tmp;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->end->counter = iter;
	que = que_add(que, mngr->end, mngr);
	while (que->offset < que->len && (child = que_popleft(que)->links))
		while (child)
		{
			if (EDGE->to->counter != iter && (EDGE->to->counter = iter))
				que = que_add(que, EDGE->to, mngr);
			if (!EDGE->was_rev)
			{
				tmp = pop_edge(&(EDGE->from->links), EDGE);
				child = child->next;
				ft_lstdelone(&tmp, NULL);
				continue ;
			}
			child = child->next;
		}
	ft_vecdel((void **)&que);
}
