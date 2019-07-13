/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/13 15:25:18 by ehugh-be         ###   ########.fr       */
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
			if (EDGE->to == &(mngr->end->wrap->in))
			{
				ft_vecdel((void **)&que);
				return (NULL);
			}
			if (!(que = push_que(que, &(EDGE->to->wrap->out), cur.priority + EDGE->wgth)))
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
** return node_of_list contains /one/ edge from /node/->/links/
*/

t_list		*pop_edge(t_list **links, t_edge *one)
{
	t_list *tmp;
	t_list *ret;

	ft_printf("try to reverse %s -> %s ", one->from->wrap->name, one->to->wrap->name); // TODO remove
	tmp = *links;
	if (tmp->data == one)
	{
		*links = tmp->next;
		return (tmp);
	}
	while (tmp->next->data != one)
		tmp = tmp->next;
	ret = tmp->next;
	tmp->next = tmp->next->next;
	return (ret);
}

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights
*/

static void		reverse_path(t_node *fin)
{
	t_edge	*path;
	t_edge	*next;
	t_list	*lst;
	t_node	*tmp;

	path = fin->path;
	while (path)
	{
		path->to->path = NULL;
		next = path->from->path;
		lst = pop_edge(&path->from->links, path);
		if (path->was_rev)
		{
			free(path);
			free(lst);
			ft_printf(" - {Green}deleted{eof} \n"); // TODO remove
		}
		else
		{
			tmp = path->from;
			path->from = path->to;
			path->to = tmp;
			path->was_rev = 1;
			ft_lstadd(&path->from->links, lst);
			ft_printf(" - {Green}reversed{eof} \n"); // TODO remove
			print_node(path->from);
			print_node(path->to);
		}
		path = next;
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

	iter = -2;
	limit = FT_MIN2(ft_lstlen(mngr->start->links),
//			ft_lstlen(((t_edge *)mngr->end->links->data)->to->links));
			ft_lstlen(mngr->end->links));
	limit = -FT_MIN2(limit, mngr->ant_num) - 1;
	ft_printf("{Blue}limit %i{eof}\n\n", -limit-1); // TODO remove
	while (iter > limit - 1)
	{
		printf("iter %i\n", iter); // TODO remove
		if (wrap_dijkstra(mngr, iter))
			break ;
		ft_printf("{Green}dijkstra done{eof}\n"); // TODO remove
		reverse_path(mngr->end);
		ft_printf("{Green}path reversed{eof}\n\n"); // TODO remove
		--iter;
	}
	return (iter);
}
