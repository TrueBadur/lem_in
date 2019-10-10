/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longest_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:43:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/10/10 19:43:43 by ehugh-be         ###   ########.fr       */
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
