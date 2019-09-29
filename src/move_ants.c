/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/29 17:01:33 by ehugh-be         ###   ########.fr       */
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

	edge->from->counter = num;
	if (mngr->fancy > 0)
	{
		mngr->input = ft_vecpush(mngr->input, "\033[38;5;", 7);
		s = ft_itoa(num % 229 + 1);
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
	return (1);
}

static void	get_one_line_hlper(int **params, t_mngr *mngr, int *cur_lem)
{
	t_edge	*edge;
	t_node	**end;

	end = (t_node **)params[1];
	edge = (t_edge *)((t_list *)params[2])->data;
	if (edge->to->counter != 0)
		*(int *)params[0] = edge->to->counter;
	else
		while (edge->to->counter == 0)
			edge = ((t_edge *)edge->to->links->data);
	while (edge->to != *end &&
	move_one_ant(edge, mngr, edge->to->counter, edge->to->wrap->name))
		edge = (t_edge *)edge->to->links->data;
	if (((t_edge*)(*end)->links->data)->to == mngr->start &&
	edge->from != mngr->end)
	{
		move_one_ant(edge, mngr, (*cur_lem)++, edge->to->wrap->name);
		if (--(*end)->counter == 0)
			*end = edge->from;
	}
	else
	{
		move_one_ant(edge, mngr, edge->to->counter, edge->to->wrap->name);
		*end = edge->from == mngr->end ? NULL : edge->from;
	}
}

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
*/

void		move_ants(t_mngr *mngr, int size)
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
		count = get_one_line((int *[]){(int *)finishs, (int *)ends}, mngr,
				&cur_lem);
		if (mngr->fancy > 0)
			ft_vecpush(mngr->input, "\33[0m", 4);
		if (!(mngr->input = ft_vecpush(mngr->input, "\n", 1)))
			ultimate_exit(mngr, MALLOC_ERROR);
	}
}
