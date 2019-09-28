/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/28 20:20:06 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 10000 * sizeof(t_pque)
#define EDGE ((t_edge *)child->data)

/*
** one run of Dijkstra algorithm trough graph,
** it sets /path/ field of /node/ from start up to finish
** and sets /counter/ field of /node/ to /iter/ (markdown of walk)
*/

/* Dijkstra algorithm consists of two functions: wrap_dijkstra and dijkstra.
 * Wrapper creates queue, puts first element in it and calls dijkstra int loop,
 * while the path isn't found and then performs cleaning.
 * dijkstra function performs checking of next node in queue and add its
 * children to the queue.
 * As a priority metric we use current path length (primary) and edge weight.
* Every launch algo has unique index (iter), using this index we check
* if current node had already been visited on this launch.
* To every child of current node, if needed we reset priority and set node from
 * which this node had been reached (path). Using this /path/ in future path
 * path will be remembered. After that each node has only one "parent" from
 * which is part of the shortest path to this node. So if startring from the end
 * there is only one path to the start and it's the shortest one.
*/

static t_vector *dijkstra(t_mngr *mngr, int iter, t_vector *que)
{
	t_pque		cur;
	t_list		*child;


	cur = pop_que(que);
	if (((t_node*)cur.data)->counter == iter)
		return (que);
	((t_node*)cur.data)->counter = iter;
	//------------------------------------------------------------------------//
#ifdef DEBUG1
	ft_printf("\n{Green}Get {\\202} %s {\\96}(%s){eof} with priority {\\207}(%d, %d){eof} from queue\n",
			((t_node*)cur.data)->wrap->name, &((t_node*)cur.data)->wrap->out == ((t_node*)cur.data) ? "out" : "in",
			cur.priority.x, cur.priority.y);
#endif
	//------------------------------------------------------------------------//
	child = ((t_node *)cur.data)->links;
	while (child)
	{
		// TODO not proceed on already set up edges
		// TODO find out why it sets wrong new labels on nodes
//
//			//------------------------------------------------------------------------//
//			t_edge * tmp2;
//			tmp2 = EDGE;
//			//-----------------------------------------------------------------------//
#ifdef DEBUG1
			ft_printf("{\\96}Checking node {Red}%s {eof}(%s)\n", EDGE->to->wrap->name,
					  &EDGE->to->wrap->out == EDGE->to ? "out" : "in", EDGE->to->label);
			ft_printf("{\\96}current priority {\\85}%d {\\96} previous {Green}%d{eof} ",
					cur.priority.x + EDGE->wgth + EDGE->from->label - EDGE->to->label, EDGE->to->path_priority.x);

#endif
			if (cur.priority + EDGE->wgth + EDGE->from->label - EDGE->to->label < EDGE->to->path_priority)
			{
				EDGE->to->path = EDGE;
				EDGE->to->path_priority = cur.priority + EDGE->wgth + EDGE->from->label - EDGE->to->label;
#ifdef DEBUG1
				ft_printf("{\\96} old label is {\\85}%d {\\96}new label will be {Green}%d{\\94} = %d + %d){eof}\n",
						  EDGE->to->label,
						  EDGE->to->label + EDGE->to->path_priority.x,
						  EDGE->to->path_priority.x,EDGE->from->label);
#endif
				if (EDGE->to->counter != iter)
					if (!(que = push_que(que, EDGE->to, EDGE->to->path_priority)))
						ultimate_exit(mngr, MALLOC_ERROR);

#ifdef DEBUG1
				ft_printf("put into que with weight {Red}(%d, %d){eof}\n", EDGE->to->path_priority.x,
						  cur.priority.y + (EDGE->was_rev ? -1 : 1));
#endif
			}
#ifdef DEBUG1
			else
				ft_printf(" label unchanged {\\94}%d{eof}\n", EDGE->to->label);
#endif
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
	mngr->start->path = NULL;
	mngr->start->path_priority = 0;
	while (que->len > 0)
		if (!(que = dijkstra(mngr, iter, que)))
		{ //todo free vector
			ft_vecdel((void**)&que);
			return (0);
		}
	ft_vecdel((void **)&que);
	if (!mngr->end->path)
	{
		ft_printf("#{Light red}cant find another way\n{eof}");
		return (-1);
	}
	return (0);
}

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights (and put it to / *log/)
** return first t_node* (after start) of this path
*/
/*
 * First get node previous to end in the shortest path in /ret/.
 * get the last edge of the path to /path/.
 * while there is at least two edges in the path:
 * increase counter ?
 * get next (previous, from what side to observe?) edge in the path in /next/.
 * pop current edge from its parent (next node) into /lst/.
 * if /path/ was reversed (/path->was_rev/ == 1 ?)
 * ...
 * else
 * 	put current edge and its current direction into log.
 * 	reverse direction of current edge and set flag about it.
 *	put edge (/lst/) into previous node
 *
 * move forward the path changing /path/ to /next/
 *
*/

static t_node	*reverse_path(t_mngr *mngr, t_node *fin, t_vector **log)
{
	t_edge	*path;
	t_edge	*next;
	t_list	*lst;
	t_node	*ret;
	t_log   one_log;

	ret = fin->path->from;
	path = fin->path;
	(*log)->offset = 0;
	while (path && path->to->path)
	{
		next = path->from->path;
		lst = pop_edge(&path->from->links, path);
#ifdef DEBUG
		ft_printf("{\\76}(%s - %s){eof} ", path->from->wrap->name, path->to->wrap->name);
#endif
		one_log = (t_log){path, path->from, path->to};
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

static void undo_reverse_path(t_vector *log)
{
	int     i;
	t_log   *logs;
	t_list	*lst;

	logs = (t_log*)log->data;
	i = -1;
	while (++i < (int)(log->len / sizeof(t_log)))
	{
		if (logs[i].edge)
		{

			lst = pop_edge(&logs[i].edge->from->links,
						   logs[i].edge); // TODO or think about all here because now it causes infinite loop

			swap_nodes(&logs[i].edge->from, &logs[i].edge->to);
			logs[i].edge->was_rev = !logs[i].edge->was_rev;
			ft_lstadd(&logs[i].edge->from->links, lst);
		}
	}
}

//------------------------------------------------------------------------//
//5
//##start
//a 0 0
//b 0 0
//c 0 0
//##end
//d 0 0
//a-b
//a-c
//c-d
//b-d
//------------------------------------------------------------------------//

/*
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
*/

#define SIZE_OF_LOG 200

int				suurballe(t_mngr *mngr, t_list **ends, int limit)
{
	int		    iter;
	int		    len_of_output;
	int         prev_len;
	t_node	    *tmp;
	t_vector   *log;
	t_vector	*all_nodes;


	iter = -2;
	//------------------------------------------------------------------------//
//	ft_printf("{Blue}limit %i{eof}\n\n", -limit - 1); // TODO print
	//------------------------------------------------------------------------//
	prev_len = 0;
	if (!(log = ft_vecinit(SIZE_OF_LOG * sizeof(t_log))))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (!(all_nodes = ft_avldatatovec(mngr->all_rooms, ft_vecinit(2 * sizeof(t_node)), &prev_len)))
		ultimate_exit(mngr, MALLOC_ERROR);
	while (iter > limit - 1)
	{
		//------------------------------------------------------------------------//
//		printf("iter %i\n", iter); // TODO print
		//------------------------------------------------------------------------//
		if (wrap_dijkstra(mngr, iter))
			break ;
		tmp = reverse_path(mngr, mngr->end, &log);
		//------------------------------------------------------------------------//
//		ft_printf("{Green}path reversed{eof}\n\n"); // TODO print
		//------------------------------------------------------------------------//
		ft_lstadd(ends, ft_lstnew(&tmp, sizeof(t_node*)));
		len_of_output = calc_len_of_output(*ends, ft_lstlen(*ends),
										   mngr->ant_num, mngr->start);
		//------------------------------------------------------------------------//
		ft_printf("#recalculate length of output {Green}%i{eof}\n", len_of_output); // TODO print
		//------------------------------------------------------------------------//

		if (prev_len && (len_of_output > prev_len || len_of_output < 0))
		{
			undo_reverse_path(log);
			break;
		}
		set_potentials(all_nodes);
		log->len = 0;
		prev_len = len_of_output;
		iter--;
	}
	return (iter);
}
