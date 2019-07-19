/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 19:06:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/19 22:03:16 by mbartole         ###   ########.fr       */
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

//	ft_printf("pop %s -> %s\n", one->from->wrap->name, one->to->wrap->name); // TODO print
	tmp = *links;
	if (tmp->data == one)
	{
		*links = tmp->next;
		return (tmp);
	}
	while (tmp->next->data != one)
		tmp = tmp->next;
	ret = tmp->next;
	tmp->next = tmp->next->next;
	return (ret);
}

#define EDGE ((t_edge *)child->data)

/*
** goes by /path/s from finish up to start and return its length
*/

int			get_path_len(t_node *node, t_node *start)
{
	int 	len;
	t_node	*cur;
	t_list	*child;

	len = 1;
	cur = node;
	while (cur != start)
	{
		child = cur->links;
		while (!EDGE->was_rev)
			child = child->next;
		if (EDGE->from->wrap != EDGE->to->wrap)
			len++;
		cur = EDGE->to;
	}
	ft_printf("local len = %i\n", len);
	return (len);
}

int			calc_len_of_output(t_list *ends, int size, int ants, t_node *start)
{
	int 	lens[size];
	int 	i;
	t_list	*tmp;
	int 	max;
	int		sum;

	i = -1;
	tmp = ends;
	max = 0;
	while (++i < size)
	{
		lens[i] = get_path_len((t_node *)tmp->data, start);
		max = lens[i] > max ? lens[i] : max;
		tmp = tmp->next;
	}
	i = -1;
	sum = 0;
	while (++i < size)
	{
		lens[i] = max - lens[i];
		sum += lens[i];
	}
	if (sum > ants)
		return (0);  // TODO if number of ants less then sum of bonus slots
	ants = (ants - sum) / size; // TODO +1
	return (max + ants - 1);
}
