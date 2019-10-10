/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/10/10 20:03:11 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define EDGE ((t_edge *)child->data)

void static inline	norminette_helper(t_node **tmp, t_edge **edge)
{
	*tmp = (*edge)->from;
	*edge = ((t_edge *)(*edge)->to->links->data);
}

static int			move_one_ant(t_edge *edge, t_mngr *mngr, int num,
		char *name)
{
	edge->from->label = num;
	add_ant_to_vec(mngr, num, name);
	return (1);
}

/*
** ant make step from previous node to next up to end-childs
** 'name' of ant are in /label/
** if there is ant in end-child node, it goes to /fins/,
** else we skip all empty nodes, then all ants make their steps
*/

static void			get_one_line_hlper(int **params, t_mngr *mngr, int *cur_lem)
{
	t_edge *edge;
	t_node **end;
	t_node *tmp;

	end = (t_node **)params[1];
	edge = (t_edge *)((t_list *)params[2])->data;
	tmp = edge->from;
	if (edge->to->label != 0)
		*(int *)params[0] = edge->to->label;
	else
		while (edge->to->label == 0)
			norminette_helper(&tmp, &edge);
	while (edge->from != *end &&
	move_one_ant(edge, mngr, edge->to->label, edge->to->wrap->name))
		norminette_helper(&tmp, &edge);
	if (edge->from->counter)
	{
		edge->from->label = *cur_lem;
		*cur_lem += 1;
		edge->from->counter--;
	}
	else
		*end = tmp == mngr->end ? NULL : tmp;
}

/*
** move all ants on one path in cycle for all paths
** first of all goes ants from /fins/ to the end
** then others, if there are more ants
*/

static int			get_one_line(int **params, t_mngr *mngr, int *cur_lem)
{
	int		count;
	int		i;
	t_list	*cur;
	int		*fins;
	t_node	**ends;

	fins = (int *)params[0];
	ends = (t_node **)params[1];
	i = -1;
	cur = mngr->end->links;
	count = 0;
	while (cur && ++i > -1)
	{
		if (fins[i])
		{
			move_one_ant((t_edge *)cur->data, mngr,\
			fins[i], mngr->end->wrap->name);
			fins[i] = 0;
		}
		if (ends[i] && ++count)
			get_one_line_hlper((int *[]){&fins[i], (int *)&ends[i], (int *)cur},
					mngr, cur_lem);
		cur = cur->next;
	}
	return (count);
}

/*
** moves ants towards finish by shortest paths first
** in /counter/ of start-childs it writes down number of ants in queue
** in /label/ of start-childs it writes down 'names' of first ants
** in /fins/ will be write down 'names' of ants that achive end->child node
** (/ends/) and ready to go to end itself. it init with nulls.
** then works while something moves
*/

void				move_ants(t_mngr *mngr, int size)
{
	int		cur_lem;
	int		count;
	int		finishs[size];
	t_node	*ends[size];

	calc_ants(mngr, ft_lstlen(mngr->end->links), ends);
	count = -1;
	while (++count < size)
	{
		ends[count]->label = count + 1;
		ends[count]->counter--;
	}
	ft_bzero(finishs, sizeof(int) * size);
	cur_lem = size + 1;
	count = 1;
	while (count)
	{
		count = get_one_line((int *[]){(int *)finishs, (int *)ends}, mngr,
				&cur_lem);
		if (mngr->fancy > 0)
			ft_vecpush(mngr->input, "\33[0m", 4);
		if (!(mngr->input = ft_vecpush(mngr->input, "\n", 1)))
			ultimate_exit(mngr, MALLOC_ERROR);
	}
}
