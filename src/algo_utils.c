/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 19:06:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/10/10 01:04:13 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** return node_of_list contains /one/ edge from /node/->/links/
*/

t_list		*pop_edge(t_list **links, t_edge *one)
{
	t_list *tmp;
	t_list *ret;

	tmp = *links;
	if (tmp->data == one)
	{
		*links = tmp->next;
		return (tmp);
	}
	while (tmp && tmp->next && tmp->next->data != one)
		tmp = tmp->next;
	if (!tmp || !tmp->next)
		return (NULL);
	ret = tmp->next;
	tmp->next = tmp->next->next;
	return (ret);
}

/*
** swap two nodes by pointers
*/

void		swap_nodes(t_node **a, t_node **b)
{
	t_node	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

#define EDGE ((t_edge *)child->data)

/*
** goes by /path/s from finish up to start and return its length
*/

int			get_path_len(t_node *node, t_node *start, char relink, t_node **set)
{
	int		len;
	t_node	*cur;
	t_list	*child;

	len = 1;
	cur = node;
	while (cur != start)
	{
		cur->counter = 0;
		if (relink)
			cur->label = 0;
		child = cur->links;
		while (!EDGE->was_rev)
			child = child->next;
		if (EDGE->from->wrap != EDGE->to->wrap)
			len++;
		cur = EDGE->to;
		if (EDGE->from->wrap == EDGE->to->wrap && relink)
		{
			EDGE->to = ((t_edge *)EDGE->to->links->data)->to;
			if (EDGE->to == start && set && (EDGE->from->counter = len + 1))
				*set = EDGE->from;
		}
	}
	return (len);
}

static int	calc_len_of_output_hlpr(int ants, int s, int size, int max)
{
	if (s >= ants)
		return (-1);
	ants = (ants - s) % size == 0 ? (ants - s) / size : (ants - s) / size + 1;
	return (max + ants - 1);
}

int			calc_len_of_output(t_list *ends, int size, int ants, t_node *start)
{
	int		lens[size];
	t_int2	count;
	t_list	*tmp;
	int		max;

	count.x = -1;
	tmp = ends;
	max = 0;
	ft_bzero(lens, size * sizeof(int));
	while (++count.x < size)
	{
		lens[count.x] = get_path_len((t_node *)tmp->data, start, 0, NULL);
		if (lens[count.x] == 1)
			return (0);
		max = lens[count.x] > max ? lens[count.x] : max;
		tmp = tmp->next;
	}
	count = (t_int2){-1, 0};
	while (++count.x < size)
	{
		lens[count.x] = max - lens[count.x];
		count.y += lens[count.x];
	}
	return (calc_len_of_output_hlpr(ants, count.y, size, max));
}
