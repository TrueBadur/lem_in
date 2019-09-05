/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:01:09 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/05 23:17:49 by ehugh-be         ###   ########.fr       */
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
		t_edge *tmp = EDGE;
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
	}
}

static int	move_one_ant(t_edge *edge, t_vector **output, int num, char *name)
{
	char	*s;

	edge->from->counter = num;
	*output = ft_vecpush(*output, "L", 1);
	s = ft_itoa(num);
	*output = ft_vecpush(*output, s, ft_strlen(s));
	free(s);
	*output = ft_vecpush(*output, "-", 1);
	*output = ft_vecpush(*output, name, ft_strlen(name));
	*output = ft_vecpush(*output, " ", 1);
	ft_printf("%s\n\n", (char *)(*output)->data); // TODO print
	return (1);
}

static void	get_one_line_hlper(int **params, t_vector **output, t_mngr *mngr,
									int *cur_lem)
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
	while (edge->to != *end && move_one_ant(edge, output, edge->to->counter,
			edge->to->wrap->name))
		edge = (t_edge *)edge->to->links->data;
	if (((t_edge*)(*end)->links->data)->to == mngr->start)
	{
		move_one_ant(edge, output, (*cur_lem)++, edge->to->wrap->name);
		if (--(*end)->counter == 0)
			*end = edge->from;
	}
	else
	{
		move_one_ant(edge, output, edge->to->counter, edge->to->wrap->name);
		*end = edge->from == mngr->end ? NULL : edge->from;
	}
}

int			get_one_line(int **params, t_vector **output, t_mngr *mngr,
							int *cur_lem)
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
			move_one_ant((t_edge *)cur->data, output,\
			fins[i], mngr->end->wrap->name);
			fins[i] = 0;
		}
		if (ends[i] && ++count)
			get_one_line_hlper((int *[]){&fins[i], (int *)&ends[i], (int *)cur},
					output, mngr, cur_lem);
		cur = cur->next;
	}
	return (count);
}
