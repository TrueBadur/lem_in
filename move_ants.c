/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/28 19:32:58 by ehugh-be         ###   ########.fr       */
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
//	ft_printf("longest path: %d\n", max);
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

//	print_node(*ends);
	max = longest_path(mngr->start, mngr->end, ends);
	sum = mngr->ant_num;
	i = -1;
	while (++i < size)
	{
		ends[i]->counter = max - ends[i]->counter;
		sum -= ends[i]->counter;
	}
//	ft_printf("sum %i\n", sum); // TODO print
	max = sum % size; // ostatok
	sum = sum / size; // po skolko v kazdoe
//	ft_printf("v kazdoe %i, ostatok %i\n", sum, max); // TODO print
	i = -1;
	while (++i < size)
	{
		ends[i]->counter += sum;
		if (max-- > 0)
			ends[i]->counter += 1;
		if (ends[i]->counter == 0)
		{
			ends[i]->counter = 1;
			ends[size - 1]->counter--;
		}
		print_node(ends[i]);
	}
}

static void	move_one_ant(t_edge *edge, t_mngr *mngr, int num, char *name)
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
//	ft_printf("%s\n\n", (char *)(*output)->data); // TODO print
}

static void get_one_line_hlper(int **params, t_mngr *mngr, int *cur_lem)
{
	t_edge	*edge;
	t_node	**end;

	end = (t_node **)params[1];
	edge = (t_edge *)((t_list *)params[2])->data;
	if (edge->to->counter != 0)
		*(int *)params[0] = edge->to->counter;
	else
		while (edge->to->counter == 0)
		{
#ifdef DEBUG
			ft_printf("{\\96}In node {Red}%s{\\96} next node is {Green}%s{eof}\n", edge->from->wrap->name, edge->to->wrap->name);
#endif
			edge = ((t_edge *) edge->to->links->data);
		}
	while (edge->to != *end)
	{
		move_one_ant(edge, mngr, edge->to->counter, edge->to->wrap->name);
		edge = (t_edge *)edge->to->links->data;
	}
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

int get_one_line(int **params, t_mngr *mngr, int *cur_lem)
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
	while (cur && ++i > -1) //TODO Here infinite loop because of changes in undone_reverse
	{
		if (fins[i])
		{
			move_one_ant((t_edge *)cur->data, mngr,\
			fins[i], mngr->end->wrap->name);
			fins[i] = 0;
		}
		if (ends[i] && ++count)
			get_one_line_hlper(
					(int *[]) {&fins[i], (int *) &ends[i], (int *) cur}, mngr,
					cur_lem);
		cur = cur->next;
	}
	return (count);
}
