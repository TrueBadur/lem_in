/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 19:06:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/29 00:03:04 by mbartole         ###   ########.fr       */
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

int			get_path_len(t_node *node, t_node *start, char to_relink, t_node **to_set)
{
	int 	len;
	t_node	*cur;
	t_list	*child;

	len = 1;
	cur = node;
	while (cur != start)
	{
		cur->counter = 0;
		child = cur->links;
		while (!EDGE->was_rev)
			child = child->next;
		if (EDGE->from->wrap != EDGE->to->wrap)
			len++;
		cur = EDGE->to;
		if (EDGE->from->wrap == EDGE->to->wrap && to_relink)
		{
			EDGE->to = ((t_edge *) EDGE->to->links->data)->to;
			if (EDGE->to == start && to_set)
			{
				EDGE->from->counter = len;
				ft_printf("{Yellow}%s - %i\n{eof}", EDGE->from->wrap->name, EDGE->from->counter);
				*to_set = EDGE->from;
			}
		}
//        if (EDGE->to == start && to_set)
//        {
//            EDGE->from->counter = len;
////            ft_printf("{Yellow}%s - %i\n{eof}", EDGE->from->wrap->name, EDGE->from->counter);
//            *to_set = EDGE->from;
//        }
	}
	ft_printf("local len = %i (%s)\n", len, EDGE->from->wrap->name); // TODO print
	return (len);
}

int			set_path_len(t_node *node, t_node *start, char to_relink, t_node **to_set)
{
    int 	len;
    t_node	*cur;
    t_list	*child;

    len = 1;
    cur = node;
    while (cur != start)
    {
        cur->counter = 0;
        child = cur->links;
        while (!EDGE->was_rev)
            child = child->next;
        if (EDGE->from->wrap != EDGE->to->wrap)
            len++;
        cur = EDGE->to;
        if (EDGE->from->wrap == EDGE->to->wrap && to_relink)
        {
            EDGE->to = ((t_edge *) EDGE->to->links->data)->to;
        }
        if (EDGE->to == start && to_set)
        {
            EDGE->from->counter = len;
//            ft_printf("{Yellow}%s - %i\n{eof}", EDGE->from->wrap->name, EDGE->from->counter);
            *to_set = EDGE->from;
        }
    }
//    ft_printf("local len = %i (%s)\n", len, EDGE->from->wrap->name); // TODO print
    return (len);
}

int			calc_len_of_output(t_list *ends, int size, int ants, t_node *start)
{
	int 	lens[size];
	int 	i;
	t_list	*tmp;
	int 	max;
	int		sum;
//	t_node  *smth;

	i = -1;
	tmp = ends;
	max = 0;
	ft_bzero(lens, size * sizeof(int));
	while (++i < size)
	{
		lens[i] = get_path_len((t_node *)tmp->data, start, 0, NULL);
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
	ants = (ants - sum) % size == 0 ? (ants - sum) / size : (ants - sum) / size + 1;
	return (max + ants - 1);
}
