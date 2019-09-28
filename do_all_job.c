/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/28 19:48:09 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** deletes all not /was_rev/ edges from graph
** (walking it by BFS from finish)
*/

static void     clean_graph(t_mngr *mngr, int iter)
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
			if (EDGE->to->counter != iter)
			{
				EDGE->to->counter = iter;
				que = que_add(que, EDGE->to, mngr);
			}
			if (!EDGE->was_rev)// && EDGE->from->wrap != EDGE->to->wrap)
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

/*
** moves ants towards finish by shortest paths first
*/

static void move_ants(t_mngr *mngr, int size)
{
	int		cur_lem;
	int		count;
	int		finishs[size];
	t_node	*ends[size];

	calc_ants(mngr, ft_lstlen(mngr->end->links), ends);
	ft_bzero(finishs, sizeof(int) * size);
	cur_lem = 1;
	count = 1;
	while (count)
	{
		count = get_one_line((int *[]) {(int *) finishs, (int *) ends}, mngr,
							 &cur_lem);
		if (!(mngr->input = ft_vecpush(mngr->input, "\n", 1)))
			ultimate_exit(mngr, MALLOC_ERROR);
	}
//	return (output);
}

/*
** overall algorithm
*/

void            do_all_job(t_mngr *mngr)
{
	int			i;
	int			size;
//	t_vector	*output;
	t_list		*ends;

//	ft_printf("{Blue}ants: %d\n\n{eof}", mngr->ant_num); // TODO print
//	set_weights(mngr);
//	ft_printf("{Green}weights set{eof}\n\n"); // TODO print
	ends = NULL;
	size = -FT_MIN2(ft_lstlen(mngr->start->links),\
	ft_lstlen(((t_edge *)mngr->end->links->data)->to->links)) - 1;
	if ((i = suurballe(mngr, &ends, size)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
	ft_lstdel(&ends, NULL);
//	ft_printf("{Blue}dijkstra has %i runs{eof}\n\n", -i - 2);  // TODO print
	clean_graph(mngr, i - 1);
	size = ft_lstlen(mngr->end->links);
//	ft_printf("{Green}graph cleaned{eof}\n\n"); // TODO print
//	if (!(output = ft_vecinit(1000 * mngr->ant_num * sizeof(char))))
//		ultimate_exit(mngr, MALLOC_ERROR);
//	ft_printf("#num of paths %i\n", size);
 	move_ants(mngr, size);
	write(STDOUT_FILENO, mngr->input->data, mngr->input->len);
//	ft_printf("\n%s", (char*)output->data);
//	ft_vecdel((void **)&output);
}
