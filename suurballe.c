/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 17:04:40 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/05 21:42:43 by ehugh-be         ###   ########.fr       */
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

void	deprioritize_queue(t_vector *vec)
{
	int i;
	t_pque *pque;

	pque = (t_pque*)vec->data;
	i = -1;
	while(++i < (int)(vec->len / sizeof(t_pque)))
		((t_node*)pque[i].data)->path_priority = (t_int2){INT32_MAX, INT32_MAX};
}

static t_vector	*dijkstra(t_mngr *mngr, int iter, t_vector *que, int prohod)
{
	t_pque		cur;
	t_list		*child;


	cur = pop_que(que);
	prohod += 0;
	t_node *tmp;
	tmp =((t_node*)cur.data);
	tmp->path_priority = (t_int2){INT32_MAX, INT32_MAX};
//	t_wnode *wnode = ft_avlsearch(mngr->all_rooms, "Fny7", 1, NULL);
//	if (wnode->in.path != NULL || wnode->out.path != NULL)
//		wnode += 0;
//	if (!ft_strcmp(tmp->wrap->name, "Bya9") || !ft_strcmp(tmp->wrap->name, "Oxc9"))
//		prohod += 0;
	if (((t_node*)cur.data)->counter == iter)
		return (que);
	if (!ft_strcmp(((t_node*)cur.data)->wrap->name, "Bcv5"))
	{
		ft_printf("\n");
		for (size_t i = 0; i < que->len / sizeof(t_pque); i++)
			ft_printf("{\\68} %s {\\69}[%d, %d]",
					  ((t_node *) ((t_pque *) que->data)[i].data)->wrap->name,
					  ((t_pque *) que->data)[i].priority.x,
					  ((t_pque *) que->data)[i].priority.y);
		ft_printf("\n");
		ft_printf("{\\202} %d %s {\\207}%d, %d{eof}", prohod, ((t_node*)cur.data)->wrap->name, cur.priority.x, cur.priority.y);
	}
//	if (prohod == 3)
//		ultimate_exit(mngr, NO_PATHS_FOUND);
	((t_node*)cur.data)->counter = iter;
	ft_printf("{\\202} %s {\\207}%d, %d{eof}", ((t_node*)cur.data)->wrap->name, cur.priority.x, cur.priority.y);
	child = ((t_node *)cur.data)->links;
	while (child)
	{
		if (EDGE->to->counter != iter)
		{
			t_edge * tmp2;
			tmp2 = EDGE;
			if(!ft_strcmp("Oxc9", EDGE->to->wrap->name))
				ft_printf("{Green} [%d, %d]{eof}", EDGE->to->path_priority.x,  EDGE->to->path_priority.y);
			if (ft_int2lt(cur.priority, EDGE->to->path_priority)) //TODO reset path_priority for all nodes set to max on extraction from queue and run through rest of the queue after path is found
			{
				EDGE->to->path = EDGE;
				EDGE->to->path_priority = cur.priority;
			}
			if (EDGE->to == mngr->end)
			{
				ft_printf("\n");
				for (size_t i = 0; i < que->len / sizeof(t_pque); i++)
					ft_printf("{\\68} %s {\\69}[%d, %d]",
							  ((t_node *) ((t_pque *) que->data)[i].data)->wrap->name,
							  ((t_pque *) que->data)[i].priority.x,
							  ((t_pque *) que->data)[i].priority.y);
				ft_printf("\n");
				ft_printf("{\\200}Price: [%d, %d] {eof}\n", cur.priority, cur.priority.y);
				deprioritize_queue(que);
				mngr->end->path_priority = (t_int2){INT32_MAX, INT32_MAX};
				ft_vecdel((void **)&que);
				return (NULL);
			}
			if (!(que = push_que(que, EDGE->to, (t_int2){cur.priority.x + EDGE->wgth, cur.priority.y + (EDGE->from->wrap == EDGE->to->wrap ? 0 : (EDGE->was_rev ? -1 : 1))})))
				ultimate_exit(mngr, MALLOC_ERROR);
//			if (!ft_strcmp(EDGE->to->wrap->name, "Frb3"))
//			{
//				ft_printf("\n");
//				for (size_t i = 0; i < que->len / sizeof(t_pque); i++)
//					ft_printf("{\\68} %s {\\69}[%d, %d]",
//							  ((t_node *) ((t_pque *) que->data)[i].data)->wrap->name,
//							  ((t_pque *) que->data)[i].priority.x,
//							  ((t_pque *) que->data)[i].priority.y);
//				ft_printf("\n");
//				ft_printf("{\\202} %d %s {\\207}%d, %d{eof}", prohod, ((t_node*)cur.data)->wrap->name, cur.priority.x, cur.priority.y);
//			}
//			print_edge(EDGE);
//			ft_printf("\n");
		}
		child = child->next;
	}
	return (que);
}
/*
** make and remove queue for Dijkstra
*/

static int		wrap_dijkstra(t_mngr *mngr, int iter, int proh)
{
	t_vector	*que;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (!(que = push_que(que, mngr->start, (t_int2){0, 0})))
		ultimate_exit(mngr, MALLOC_ERROR);
//	mngr->start->counter = iter;
	mngr->start->path = NULL;
	while (que->len > 0)
		if (!(que = dijkstra(mngr, iter, que, proh))){
//			t_wnode* tmp = ft_avlsearch(mngr->all_rooms, "Frb3", 1, NULL);
//			print_node(&tmp->in);
//			print_node(&tmp->out);
			return (0);}

	ft_vecdel((void **)&que);
	ft_printf("{Light red}#cant find another way\n{eof}");
	return (-1);
}

/*
** goes by /path/s from finish up to start,
** reverses or/and delete edges, switch weights (and put it to / *log/)
** return first t_node* (after start) of this path
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
	int i = 0;
    while (path && path->to->path)
	{
		i++;
    	next = path->from->path;
		lst = pop_edge(&path->from->links, path);
		if (path->was_rev)
		{
			if (path->to->wrap == path->from->wrap)  // TODO think about log
			{
				one_log = (t_log){path, path->from, path->to};
				swap_nodes(&path->from, &path->to);
				path->was_rev = 0;
				ft_lstadd(&path->from->links, lst);
			}
			else
			{one_log = (t_log){NULL, path->from, path->to};
			free(path);
			free(lst);}
		}
		else
		{
            one_log = (t_log){path, path->from, path->to};
			swap_nodes(&path->from, &path->to);
			path->was_rev = 1;
			ft_lstadd(&path->from->links, lst);
		}
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

static void     undo_reverse_path(t_mngr *mngr, t_vector *log)
{
    int     i;
    t_log   *logs;
    t_edge  *ed;
//
    logs = (t_log*)log->data;
    i = -1;
//    ft_printf("{Blue}LOG: {eof}");
    while (++i < (int)(log->len / sizeof(t_log))) {
        if (logs[i].edge)
        {
            pop_edge(&logs[i].edge->from->links, logs[i].edge);
        }
        else
        {
            if (!(ed = malloc(sizeof(t_edge))))
                ultimate_exit(mngr, MALLOC_ERROR);
            ed->wgth = -1;
            ed->from = logs[i].from;
            ed->to = logs[i].to;
            ed->was_rev = 1;
            ft_lstadd(&logs[i].from->links, ft_lstnew(ed, sizeof(t_edge)));
            free(ed);
        }
    }
}

/*
** run Dijkstra and reversing paths while can or while it has sense
** return negative value of iteration where it stopped
*/

#define SIZE_OF_LOG 200
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
int				suurballe(t_mngr *mngr, t_list **ends, int limit)
{
	int		    iter;
	int		    len_of_output;
	int         prev_len;
	t_node	    *tmp;
	t_vector   *log;


	iter = -2;
//	ft_printf("{Blue}limit %i{eof}\n\n", -limit - 1); // TODO print
	prev_len = 0;
	if (!(log = ft_vecinit(SIZE_OF_LOG * sizeof(t_log))))
	    ultimate_exit(mngr, MALLOC_ERROR);
	int p = 1;
	while (iter > limit - 1)
	{
//		printf("iter %i\n", iter); // TODO print
		if (wrap_dijkstra(mngr, iter, p++))
			break ;
		tmp = reverse_path(mngr, mngr->end, &log);
//		ft_printf("{Green}path reversed{eof}\n\n"); // TODO print
		ft_lstadd(ends, ft_lstnew(&tmp, sizeof(t_node*)));
		len_of_output = calc_len_of_output(*ends, ft_lstlen(*ends),
				mngr->ant_num, mngr->start);
        ft_printf("#recalculate length of output {Green}%i{eof}\n", len_of_output); // TODO print
		if (prev_len && (len_of_output > prev_len || len_of_output < 0))
		{
		    undo_reverse_path(mngr, log);
            ft_printf("\n{Green}reverse undone{eof}\n\n"); // TODO print
            break;
        }
        log->len = 0;
        ft_bzero(log->data, log->cap); // TODO not nec
		prev_len = len_of_output;
		--iter;
	}
	return (iter);
}
