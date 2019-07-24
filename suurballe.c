/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/24 19:23:07 by mbartole         ###   ########.fr       */
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
			{
				ft_vecdel((void **)&que);
				return (NULL);
			}
			if (!(que = push_que(que, EDGE->to, cur.priority + EDGE->wgth)))
				ultimate_exit(mngr, MALLOC_ERROR);
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
		ultimate_exit(mngr, MALLOC_ERROR);
	if (!(que = push_que(que, mngr->start, 0)))
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->start->counter = iter;
	mngr->start->path = NULL;
	while (que->len > 0)
		if (!(que = dijkstra(mngr, iter, que)))
			return (0);
	ft_vecdel((void **)&que);
	return (-1);
}

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights
** return first t_node* (after start) of this path
*/

static t_node	*reverse_path(t_node *fin)
{
	t_edge	*path;
	t_edge	*next;
	t_list	*lst;
	t_node	*ret;

	ret = fin->path->from;
	path = fin->path;
	while (path && !(path->to->path = NULL))
	{
		next = path->from->path;
		lst = pop_edge(&path->from->links, path);
		if (path->was_rev)
		{
			free(path);
			free(lst);
		}
		else
		{
			swap_nodes(&path->from, &path->to);
			path->was_rev = 1;
			ft_lstadd(&path->from->links, lst);
		}
		path = next;
	}
	return (ret);
}

/*
** goes by /path/s from finish up to start and return its length
*/

static int		get_new_path_len(t_node *fin)
{
	t_edge	*path;
	t_list	*child;
	int		len;

	len = 0;
	path = fin->path;
	while (path)
	{
		if (path->from->wrap != path->to->wrap)
		{
			len++;
			child = path->from->links;
			while (child)
			{
				if (EDGE == path && EDGE->was_rev)
				{
					len -= 2;
					break ;
				}
				child = child->next;
			}
		}
		path = path->from->path;
	}
//	ft_printf("len of new path %i\n", len);
	return (len);
}

/*
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
*/

int				suurballe(t_mngr *mngr, t_list **ends)
{
	int		iter;
	int		limit;
	int		len_of_output;
	t_node	*tmp;
	t_list	*lst;

	iter = -2;
	limit = -FT_MIN2(ft_lstlen(mngr->start->links),
			ft_lstlen(((t_edge *)mngr->end->links->data)->to->links)) - 1;
//	ft_printf("{Blue}limit %i{eof}\n\n", -limit - 1); // TODO print
	len_of_output = 0;
	while (iter > limit - 1)
	{
//		printf("iter %i\n", iter); // TODO print
		if (wrap_dijkstra(mngr, iter))
			break ;
//		ft_printf("{Green}dijkstra done{eof}, "); // TODO print
		if (len_of_output && (get_new_path_len(mngr->end) >= len_of_output))
			break ;
		tmp = reverse_path(mngr->end);
		lst = ft_lstnew(&tmp, sizeof(t_node*));
//		ft_printf("{Green}path reversed{eof}\n\n"); // TODO print
		ft_lstadd(ends, lst);
		len_of_output = calc_len_of_output(*ends, ft_lstlen(*ends),
				mngr->ant_num, mngr->start);
//		ft_printf("recalculate length of output {Green}%i{eof}\n\n", len_of_output); // TODO print
		--iter;
	}
	return (iter);
}
