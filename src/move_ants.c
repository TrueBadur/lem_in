/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/10/09 22:59:40 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define EDGE ((t_edge *)child->data)

/*
** set array /ends/ and get length of the longest path
*/

int			longest_path(t_node *start, t_node *end, t_node **ends)
{
	t_list	*child;
	int		i;
	int		max;
	int		len;

	max = 0;
	child = end->links;
	i = -1;
	while (child)
	{
		len = get_path_len(EDGE->to, start, 1, &ends[++i]);
		max = len > max ? len : max;
		child = child->next;
	}
	return (max);
}

static int	move_one_ant(t_edge *edge, t_mngr *mngr, int num, char *name)
{
	char	*s;

	edge->from->label = num;
	if (mngr->fancy > 0)
	{
		mngr->input = ft_vecpush(mngr->input, "\033[38;5;", 7);
		s = ft_itoa(num);
		mngr->input = ft_vecpush(mngr->input, s, ft_strlen(s));
		mngr->input = ft_vecpush(mngr->input, "m", 1);
	}
	mngr->input = ft_vecpush(mngr->input, "L", 1);
	s = ft_itoa(num);
	mngr->input = ft_vecpush(mngr->input, s, ft_strlen(s));
	free(s);
	mngr->input = ft_vecpush(mngr->input, "-", 1);
	mngr->input = ft_vecpush(mngr->input, name, ft_strlen(name));
	if (!(mngr->input = ft_vecpush(mngr->input, " ", 1)))
		ultimate_exit(mngr, MALLOC_ERROR);
//	ft_printf(mngr->input->data);
	return (1);
}

/*
** ant make step from previous node to next up to end-childs
** 'name' of ant are in /label/
** if there is ant in end-child node, it goes to /fins/,
** else we skip all empty nodes, then all ants make their steps
*/

static void	get_one_line_hlper(int **params, t_mngr *mngr, int *cur_lem) {
	t_edge *edge;
	t_node **end;

	end = (t_node **) params[1];
	edge = (t_edge *) ((t_list *) params[2])->data;
	if (edge->to->label != 0)
		*(int *) params[0] = edge->to->label;
	else
		while (edge->to->label == 0)
			edge = ((t_edge *) edge->to->links->data);
	while (edge->to != *end &&
		   move_one_ant(edge, mngr, edge->to->label, edge->to->wrap->name))
		edge = (t_edge *) edge->to->links->data;
	if (edge->to->counter)
	{
		edge->to->label = *cur_lem;
		*cur_lem += 1;
		edge->to->counter--;
	}
	else
		*end = edge->from == mngr->end ? NULL : edge->from;
}

/*
** move all ants on one path in cycle for all paths
** first of all goes ants from /fins/ to the end
** then others, if there are more ants
*/

static int	get_one_line(int **params, t_mngr *mngr, int *cur_lem)
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
** in /fins/ will be write down 'names' of ants that achive end->child node (/ends/)
**  and ready to go to end itself. it init with nulls.
** then works while something moves
*/


void		move_ants(t_mngr *mngr, int size)
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
