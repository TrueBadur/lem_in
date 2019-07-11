/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/11 16:52:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 100 * sizeof(t_pque)
#define EDGE ((t_edge *)child->data)

/*
** one run of Dijkstra algorithm trough graph,
** it sets /path/ field of /node/ from start up to finish
** and sets /counter/ field of /node/ to /iter/ (markdown of walk)
*/

static t_vector	*dijkstra(t_mngr *mngr, int iter, t_vector *que)
{
	t_pque		cur;
	t_list		*child;

	cur = pop_que(que);
	child = ((t_node *)cur.data)->links;
	while (child)
	{
		if (EDGE->to->counter != iter)
		{
			EDGE->to->counter = iter;
			EDGE->to->path = EDGE;
			if (EDGE->to == mngr->end)
				return (NULL);
			if (!(que = push_que(que, EDGE->to, cur.priority + EDGE->wgth)))
				ultimate_exit(&mngr);
		}
		child = child->next;
	}
	return (que);
}

/*
** make and remove queue for Dijkstra
*/

static int		wrap_dijkstra(t_mngr *mngr, int iter)
{
	t_vector	*que;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(&mngr);
	if (!(que = push_que(que, mngr->start, 0)))
		ultimate_exit(&mngr);
	mngr->start->counter = iter;
	mngr->start->path = NULL;
	while (que->len > 0)
		if (!(que = dijkstra(mngr, iter, que)))
		{
			ft_vecdel((void **)&que);
			return (0);
		}
	ft_vecdel((void **)&que);
	return (-1);
}

/*
** delete one link from /node/->/links/
*/

void			del_from_links(t_list **links, t_edge *one)
{
	t_list *tmp;
	t_list *del;

	printf("try to delete %s -> %s ", one->from->name, one->to->name); // TODO remove
	tmp = *links;
	if (tmp->data == one)
	{
		*links = tmp->next;
		free(tmp);
		printf(" - deleted \n"); // TODO remove
		return ;
	}
	while (tmp->next->data != one)
		tmp = tmp->next;
	del = tmp->next;
	tmp->next = del->next;
	free(del);
	printf(" - deleted \n"); // TODO remove
}

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights
*/

static void		reverse_path(t_node *fin)
{
	t_edge	*path;
	t_edge	*del;

	path = fin->path;
	while (path)
	{
		path->to->path = NULL;
		if (path->reverse)
		{
			path->reverse->wgth = path->wgth;
			path->reverse->reverse = NULL;
		}
		del_from_links(&path->from->links, path);
		del = path;
		path = path->from->path;
		free(del);
	}
}

/*
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
*/

int				suurballe(t_mngr *mngr)
{
	int	iter;
	int	limit;

	iter = -1;
	limit = -MIN(ft_lstlen(mngr->start->links), ft_lstlen(mngr->end->links));
	limit = -MIN(limit, mngr->ant_num) - 1;
	while (iter > limit)
	{
		--iter;
		printf("limit %i, iter %i\n", limit, iter); // TODO remove
		if (wrap_dijkstra(mngr, iter))
			break ;
		printf("dijkstra done\n"); // TODO remove
		reverse_path(mngr->end);
		printf("path reversed\n"); // TODO remove
	}
	return (iter);
}
