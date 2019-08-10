/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/08/10 20:13:26 by mbartole         ###   ########.fr       */
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

static t_node	*reverse_path(t_node *fin, t_log **log)
{
    t_edge	*path;
    t_edge	*next;
    t_list	*lst;
    t_node	*ret;

    log++; //TODO del
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
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
 * /ends/ - last (before start) nodes of reversed accepted paths
*/

int				suurballe(t_mngr *mngr, t_list **ends, int limit)
{
	int		iter;
	int		len_of_output;
	int     prev_len_of_output;
	t_node	*tmp;
	t_log   log[mngr->ant_num];

	iter = -2;
	prev_len_of_output = 0;
	while (iter > limit - 1)
	{
		if (wrap_dijkstra(mngr, iter))
			break ;
		tmp = reverse_path(mngr->end, (t_log**)&log);
        ft_lstadd(ends, ft_lstnew(&tmp, sizeof(t_node*)));
        ft_printf("{Green}path reversed{eof}\n\n"); // TODO print
		len_of_output = calc_len_of_output(*ends, ft_lstlen(*ends),
				mngr->ant_num, mngr->start);
        ft_printf("recalculate length of output {Green}%i{eof}\n\n", len_of_output); // TODO print
        if (prev_len_of_output && (len_of_output > prev_len_of_output))
        {
//            undo();
            break ;
        }
        prev_len_of_output = len_of_output;
		--iter;
	}
	return (iter);
}
