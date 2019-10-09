/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/29 13:42:33 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 10000 * sizeof(t_pque)
#define EDGE ((t_edge *)child->data)

static t_vector	*dijkstra(t_mngr *mngr, int iter, t_vector *que)
{
	t_pque		cur;
	t_list		*child;

	cur = pop_que(que);
	if (((t_node*)cur.data)->counter == iter)
		return (que);
	((t_node*)cur.data)->counter = iter;
	child = ((t_node *)cur.data)->links;
	while (child)
	{
		if (EDGE->to->counter != iter && cur.priority + EDGE->wgth +
		EDGE->from->label - EDGE->to->label < EDGE->to->tmp_label)
		{
			EDGE->to->tmp_path = EDGE;
			EDGE->to->tmp_label = cur.priority + EDGE->wgth +
					EDGE->from->label - EDGE->to->label;
			if (!(que = push_que(que, EDGE->to, EDGE->to->tmp_label)))
				ultimate_exit(mngr, MALLOC_ERROR);
		}
		child = child->next;
	}
	((t_node*)cur.data)->label += ((t_node*)cur.data)->tmp_label;
	((t_node*)cur.data)->tmp_label = INT32_MAX;
	((t_node*)cur.data)->path = ((t_node*)cur.data)->tmp_path;
	return (que);
}

/*
** make and remove queue for Dijkstra
*/

static int		wrap_dijkstra(t_mngr *mngr, int iter)
{
	t_vector	*que;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (!(que = push_que(que, mngr->start, 0)))
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->start->path = NULL;
	mngr->start->tmp_label = 0;
	while (que->len > 0)
		if (!(que = dijkstra(mngr, iter, que)))
		{
			ft_vecdel((void**)&que);
			return (0);
		}
	ft_vecdel((void **)&que);
	if (!mngr->end->path)
		return (-1);
	return (0);
}

/*
** goes by /path/s from finish up to start,
** reverses edges, switch weights (and put it to / *log/)
** return first t_node* (after start) of this path
*/

static t_node	*reverse_path(t_mngr *mngr, t_node *fin, t_vector **log)
{
	t_edge	*path;
	t_edge	*next;
	t_list	*lst;
	t_node	*ret;
	t_log	one_log;

	ret = fin->path->from;
	path = fin->path;
	(*log)->offset = 0;
	while (path && path->to->path)
	{
		next = path->from->path;
		lst = pop_edge(&path->from->links, path);
		one_log = (t_log){path, path->to};
		(*log)->offset += path->wgth;
		swap_nodes(&path->from, &path->to);
		path->was_rev = path->was_rev == 1 ? 0 : 1;
		path->wgth = -path->wgth;
		ft_lstadd(&path->from->links, lst);
		path->from->path = NULL;
		path = next;
		if (!(*log = ft_vecpush(*log, &one_log, sizeof(t_log))))
			ultimate_exit(mngr, MALLOC_ERROR);
	}
	return (ret);
}

/*
** goes by /log/,
** undo all reverses or/and deletes of edges
*/

static int		undo_reverse_path(t_vector *log)
{
	int		i;
	t_log	*logs;
	t_list	*lst;

	logs = (t_log*)log->data;
	i = -1;
	while (++i < (int)(log->len / sizeof(t_log)))
	{
		if (logs[i].edge)
		{
			lst = pop_edge(&logs[i].edge->from->links, logs[i].edge);
			swap_nodes(&logs[i].edge->from, &logs[i].edge->to);
			logs[i].edge->was_rev = !logs[i].edge->was_rev;
			ft_lstadd(&logs[i].edge->from->links, lst);
		}
	}
	return (1);
}

/*
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
*/

int				suurballe(t_mngr *mngr, t_list **ends, int limit)
{
	int			iter;
	int			len_of_output;
	int			prev_len;
	t_node		*tmp;
	t_vector	*log;

	iter = -1;
	prev_len = 0;
	if (!(log = ft_vecinit(MY_LOG)))
		ultimate_exit(mngr, MALLOC_ERROR);
	while (--iter > limit - 1)
	{
		if (wrap_dijkstra(mngr, iter))
			break ;
		tmp = reverse_path(mngr, mngr->end, &log);
		ft_lstadd(ends, ft_lstnew(&tmp, sizeof(t_node*)));
		len_of_output = calc_len_of_output(*ends, ft_lstlen(*ends),
				mngr->ant_num, mngr->start);
		if (!len_of_output)
			move_all_at_once(mngr);
		if (prev_len && (len_of_output > prev_len || len_of_output < 0) &&
		undo_reverse_path(log))
			break ;
		log->len = 0;
		prev_len = len_of_output;
	}
	return (iter);
}
