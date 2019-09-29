/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/29 12:56:52 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define EDGE ((t_edge *)child->data)

/*
** set array /ends/ and get length of the longest path
*/

static int	longest_path(t_node *start, t_node *end, t_node **ends)
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

/*
** calculate total number of ants for every path,
** write it down to /node->counter/ for start of path
** (in fact it's /mngr->start->child/s)
*/

void		calc_ants(t_mngr *mngr, int size, t_node **ends)
{
	int		max;
	int		sum;
	int		i;

	max = longest_path(mngr->start, mngr->end, ends);
	sum = mngr->ant_num;
	i = -1;
	while (++i < size)
	{
		ends[i]->counter = max - ends[i]->counter;
		sum -= ends[i]->counter;
	}
	max = sum % size;
	sum = sum / size;
	i = -1;
	while (++i < size)
	{
		ends[i]->counter += sum;
		if (max-- > 0)
			ends[i]->counter += 1;
		if (ends[i]->counter == 0 && (ends[i]->counter = 1))
			ends[size - 1]->counter--;
	}
}

static int	move_one_ant(t_edge *edge, t_mngr *mngr, int num, char *name)
{
	char	*s;

	edge->from->counter = num;
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
	if (((t_edge*)(*end)->links->data)->to == mngr->start)
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

int			get_one_line(int **params, t_mngr *mngr, int *cur_lem)
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
