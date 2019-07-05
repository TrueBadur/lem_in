/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:05:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/05 19:05:08 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define QUE_SIZE 1000

void	que_add(t_vector *que, t_node *node, int depth)
{
	ft_vecpush(que, (long[]){(long)node,(long)depth}, sizeof(long)*2);
}

void	que_popleft(t_vector *que)
{
	que->offset += sizeof(long)*2;
}

t_node	*que_get_node(t_vector *que)
{
	return ((t_node *)(((long*)que)[0]));
}

int		que_get_depth(t_vector *que)
{
	return ((int)(((long*)que)[1]));
}

void	bfs(t_node *root)
{
	t_vector	*que;
	t_node		*cur;
	int 		depth;
	t_list		*child;

	que = ft_vecinit(sizeof(t_node) * QUE_SIZE);
	que_add(que, root, 0);
	while (que->offset != que->len)
	{
		cur = que_get_node(que);
		depth = que_get_depth(que);
		que_popleft(que);
		if (cur->wgth != -1)
			continue;
		cur->wgth = depth;
		child = cur->links;
		while (child)
		{
			que_add(que, child->data, depth + 1);
			child = child->next;
		}
	}
}