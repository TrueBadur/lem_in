/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:31:08 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/09 21:11:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_que(t_pque *q, int n)
{
	int i;

	i = -1;
	while (++i < n)
		printf("priority: %i | %c\n", q[i].priority, *(char *)(q[i].data));
}

static void	swap_pque(t_pque *a, t_pque *b)
{
	t_pque	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sift_up(t_pque *q, unsigned int i)
{
	unsigned int	parent;

	if (i == 0)
		return ;
	parent = (i + 1) / 2 - 1;
	if (q[i].priority < q[parent].priority)
		swap_pque(&q[i], &q[parent]);
	sift_up(q, parent);
}

#define MIN(x, y) (x < y ? x : y)

static void	sift_down(t_pque *q, unsigned int i, unsigned int len)
{
	unsigned int lft;
	unsigned int rght;

	if ((lft = 2 * i + 1) >= len)
		return ;
	if ((rght = 2 * i + 2) >= len)
	{
		if (q[lft].priority < q[rght].priority)
			swap_pque(&q[lft], &q[rght]);
		return ;
	}
	if (q[i].priority > MIN(q[lft].priority, q[rght].priority))
	{
		if (q[lft].priority <= q[rght].priority)
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

void		push_que(t_vector *vec, void *data, int priority)
{
	ft_vecpush(vec, (int *[]){(int *)data, (int *)(long)priority},
			sizeof(t_pque));
	sift_up((t_pque *)(vec->data), vec->len / sizeof(t_pque) - 1);
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