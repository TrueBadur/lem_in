/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/08/10 22:29:03 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** deletes all not /was_rev/ edges from graph
** (walking it by BFS from finish)
*/

static void	clean_graph(t_mngr *mngr, int iter)
{
	t_vector	*que;
	t_list		*child;
	t_list		*tmp;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->end->counter = iter;
	que = que_add(que, mngr->end, mngr);
	while (que->offset != que->len && (child = que_popleft(que)->links))
		while (child)
		{
			if (EDGE->to->counter != iter)
			{
				EDGE->to->counter = iter;
				que = que_add(que, EDGE->to, mngr);
			}
			if (!EDGE->was_rev)
			{
				tmp = pop_edge(&(EDGE->from->links), EDGE);
				ft_lstdelone(&tmp, NULL);
				break ;
			}
			child = child->next;
		}
	ft_vecdel((void **)&que);
}

/*
** moves ants towards finish by shortest paths first
*/

static t_vector	*move_ants(t_mngr *mngr, t_vector *output, int size)
{
	int		cur_lem;
	int		count;
	int		finishs[size];
	t_node	*ends[size];

	calc_ants(mngr, ft_lstlen(mngr->end->links), ends);
//	int i = -1;  // TODO print
//	while (++i < size)  // TODO print
//		print_node(ends[i]);  // TODO print
	ft_bzero(finishs, sizeof(int) * size);
	cur_lem = 1;
	count = 1;
	while (count)
	{
		count = get_one_line((int*[]){(int *)finishs, (int *)ends}, &output,
							 mngr, &cur_lem);
		output = ft_vecpush(output, "\n", 1);
	}
	return (output);
}

static void	set_path_len(t_list *starts, t_node *start)
{
    int 	len;
    t_node	*cur;
    t_list	*child;

    while (starts)
    {
        len = 1;
        cur = (t_node *)starts->data;
        while (cur != start) {
            cur->counter = 0;
            child = cur->links;
            while (!EDGE->was_rev)
                child = child->next;
            if (EDGE->from->wrap != EDGE->to->wrap) {
//                ft_printf("/ {Green}%s{eof} /", cur->wrap->name); // TODO print
                len++;
            }
            cur = EDGE->to;
//        if (EDGE->from->wrap == EDGE->to->wrap && to_relink)
//        {
//            EDGE->to = ((t_edge *) EDGE->to->links->data)->to;
//        }
            if (EDGE->to == start)
//        {
                EDGE->from->counter = len;
//            ft_printf("{Yellow}%s - %i\n{eof}", EDGE->from->wrap->name, EDGE->from->counter);
//            *to_set = EDGE->from;
//        }
        }
    ft_printf("local len = %i (%s)\n", len, EDGE->from->wrap->name); // TODO print
        starts = starts->next;
    }
//    return (len);
}


/*
** overall algorithm
** /starts/ - first (after start) nodes of accepted paths
** (as well paths are reversed, it really ends of paths)
*/

void		do_all_job(t_mngr *mngr)
{
	int			i;
	int			size;
	t_vector	*output;
	t_list		*starts;

	set_weights(mngr);
//	ft_printf("{Green}weights set{eof}\n\n"); // TODO print
	starts = NULL;
    size = -FT_MIN2(ft_lstlen(mngr->start->links),
                     ft_lstlen(((t_edge *)mngr->end->links->data)->to->links)) - 1;
    //	ft_printf("{Blue}limit %i{eof}\n\n", -size - 1); // TODO print
	if ((i = suurballe(mngr, &starts, size)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
    set_path_len(starts, mngr->start);
	ft_lstdel(&starts, NULL);
	ft_printf("{Blue}dijkstra has %i runs{eof}\n\n", -i - 2);  // TODO print
	clean_graph(mngr, i - 1);
	size = ft_lstlen(mngr->end->links);
	ft_printf("{Green}graph cleaned{eof}\n\n"); // TODO print
	if (!(output = ft_vecinit(1000 * mngr->ant_num * sizeof(char))))
		ultimate_exit(mngr, MALLOC_ERROR);
//	ft_printf("#num of paths %i\n", size);
	output = move_ants(mngr, output, size);
	ft_printf("\n%s", (char*)output->data);
	ft_vecdel((void **)&output);
}
