/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:31:08 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/27 16:05:13 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pque.h"

/*
** swap two elements in Queue
*/

static void	swap_pque(t_pque *a, t_pque *b)
{
	t_pque	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int ft_int2lt(t_int2 a, t_int2 b)
{
//	return a.y < b.y;
//	return (a.y < b.y || (a.y == b.y && a.x < b.x));
	return (a.x < b.x );//|| (a.x == b.x && a.y < b.y));
}

t_int2 ft_int2_min(t_int2 a, t_int2 b){
	return (ft_int2lt(a, b) ? a : b);
}

int ft_int2gt(t_int2 a, t_int2 b)
{
//	return a.y > b.y;
//	return (a.y > b.y || (a.y == b.y && a.x < b.x));
	return (a.x > b.x );//|| (a.x == b.x && a.y > b.y));
}

int ft_int2eq(t_int2 a, t_int2 b)
{
	return (a.x == b.x && a.y == b.y);
}

/*
** sift minimal element up by PriorityQueue
*/

static void	sift_up(t_pque *q, unsigned int i)
{
	unsigned int	parent;

	if (i == 0)
		return ;
	parent = (i + 1) / 2 - 1;
	if (ft_int2lt(q[i].priority, q[parent].priority))
	{
		swap_pque(&q[i], &q[parent]);
		sift_up(q, parent);
	}
}

/*
** sift maximal element down by PriorityQueue
*/

static void	sift_down(t_pque *q, unsigned int i, unsigned int len)
{
	unsigned int lft;
	unsigned int rght;

	if ((lft = 2 * i + 1) >= len)
		return ;
	if ((rght = 2 * i + 2) >= len)
	{
		if (ft_int2lt(q[lft].priority, q[i].priority))
			swap_pque(&q[lft], &q[i]);
		return ;
	}
	if (ft_int2gt(q[i].priority, ft_int2_min(q[lft].priority, q[rght].priority)))
	{
		if (ft_int2lt(q[lft].priority, q[rght].priority) || ft_int2eq(q[lft].priority, q[rght].priority))
		{
			swap_pque(&q[i], &q[lft]);
			sift_down(q, lft, len);
		}
		else
		{
			swap_pque(&q[i], &q[rght]);
			sift_down(q, rght, len);
		}
	}
}

/*
** add any Data with some Priority to PriorityQueue:
** append it to the end and then Sift_Up to its place
*/

void		*push_que(t_vector *vec, void *data, t_int2 priority)
{
	if (!(vec = ft_vecpush(vec, &((t_pque){data, priority}), sizeof(t_pque))))
		return (NULL);
	sift_up((t_pque *)(vec->data), vec->len / sizeof(t_pque) - 1);
	return (vec);
}

/*
** pop Data from PriorityQueue with minimum priority:
** get first element,
** then put last element on 1st place and Sift_Down to its place
*/

t_pque		pop_que(t_vector *vec)
{
	t_pque			*que;
	t_pque			ret;
	unsigned int	len;

	que = (t_pque *)(vec->data);
	ret.priority = que[0].priority;
	ret.data = que[0].data;
	len = vec->len / sizeof(t_pque) - 1;
	que[0].priority = que[len].priority;
	que[0].data = que[len].data;
	vec->len -= sizeof(t_pque);
	ft_bzero((void *)(vec->data + vec->len), sizeof(t_pque));
	sift_down(que, 0, len);
	return (ret);
}
