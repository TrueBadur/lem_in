/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/16 17:42:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define SIZE_OF_QUE 1000 * sizeof(t_node)
#define EDGE ((t_edge *)child->data)

/*
** deletes all not /was_rev/ edges from graph
** (walking it by BFS from finish)
*/

void	clean_graph(t_mngr *mngr, int iter)
{
	t_vector	*que;
	t_node		*cur;
	t_list		*child;
	t_list		*tmp;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	mngr->end->counter = iter;
	que = que_add(que, mngr->end, mngr);
	while (que->offset != que->len)
	{
		cur = que_popleft(que);
		child = cur->links;
		while (child)
		{
			if (EDGE->to->counter != iter)
			{
				EDGE->to->counter = iter;
				que = que_add(que, EDGE->to, mngr);
			}
			if (!EDGE->was_rev)
			{
				tmp = pop_edge(&(EDGE->from->links), EDGE);
				free(tmp->data);
				free(tmp);
			}
			child = child->next;
		}
//		print_node(cur); // TODO remove
	}
	ft_vecdel((void **)&que);
}

char 	*print_one_lem(int num, char *name)
{
	char *s;

	s = ft_strjoin("L", ft_itoa(num));
	s = ft_strjoin(s, "-");
	s = ft_strjoin(s, name);
	s = ft_strjoin(s, " ");
//	ft_printf("%s", s); // TODO print
	return (s);
}

#define EDGE2 ((t_edge *)ends[i]->links->data)

t_vector	*calc_lens_of_paths(t_vector *que, t_mngr *mngr, t_node **ends)
{
	int			cur_path_len;
	t_list		*cur;
	int 		i;

	i = 0;
	cur = mngr->end->links;
	while (cur)
	{
//		print_node(((t_edge*)cur->data)->from);  // TODO remove
		ends[i] = ((t_edge*)cur->data)->to;
		cur_path_len = 2;
		while (EDGE2->to != mngr->start)
		{
			ends[i]->counter = 0;
			if (EDGE2->from->wrap == EDGE2->to->wrap)
				EDGE2->to = ((t_edge *)EDGE2->to->links->data)->to;
			else
			{
				cur_path_len++;
//				print_node(ends[i]); // TODO remove
				ends[i] = EDGE2->to;
			}
		}
//		print_node(ends[i]);  // TODO remove
		if (!(que = push_que(que, ends[i], cur_path_len)))
			ultimate_exit(mngr, MALLOC_ERROR);
//		printf("len = %i\n", cur_path_len); // TODO remove
		cur = cur->next;
		i++;
	}
//	ft_printf("{Blue}%i ants at all{eof}\n", mngr->ant_num); // TODO remove
	return (que);
}

/*
** calculate total number of ants for every path,
** write it down to /node->counter/ for start of path
** (in fact it's /mngr->start->child/s)
*/

//TODO fast calculation after all weights are equal
void		calc_ants(t_mngr *mngr, int n, t_node **ends)
{
	t_vector	*que;
	t_pque		cur;

	if (!(que = ft_vecinit(SIZE_OF_QUE)))
		ultimate_exit(mngr, MALLOC_ERROR);
	que = calc_lens_of_paths(que, mngr, ends);
	while (n > 0)
	{
		cur = pop_que(que);
		((t_node *)cur.data)->counter++;
		n--;
		if (!(que = push_que(que, cur.data, cur.priority + 1)))
			ultimate_exit(mngr, MALLOC_ERROR);
	}
	ft_vecdel((void **)&que);
}

void			move_one_ant(t_edge *edge, t_vector **output, int num, char *name)
{
	char 	*one;

	edge->from->counter = num;
	one = print_one_lem(num, name);
	*output = ft_vecpush(*output, one, ft_strlen(one)); // TODO free
}

/*
** moves ants towards finish by shortest paths first
*/

t_vector 		*move_lems(t_mngr *mngr, t_vector *output, int size)
{
	int cur_lem;
	int count;
	t_list	*cur;
	t_edge	*edge;
	t_node	*ends[size];
	int		finishs[size];
	int 	i;

	ft_bzero(ends, sizeof(t_node*) * size);
	ft_bzero(finishs, sizeof(int) * size);
	calc_ants(mngr, mngr->ant_num, ends);
	i = -1;
	while (++i < size)
	{
//		print_node(ends[i]); // TODO remove
		if (ends[i]->counter == 0)
			ends[i] = NULL;
	}
//	printf("\n\n");  // TODO remove
	cur_lem = 1;
	count = 1;
	while (count)
	{
		i = -1;
		cur = mngr->end->links;
		count = 0;
		while (++i < size)
		{
			if (finishs[i])
				move_one_ant((t_edge *)cur->data, &output, finishs[i], mngr->end->wrap->name);
			if (ends[i] && ++count)
			{
				edge = (t_edge *)cur->data;
				if (edge->to->counter != 0)
					finishs[i] = edge->to->counter;
				else
					while (edge->to->counter == 0)  // just pass
						edge = ((t_edge *)edge->to->links->data);
				while (edge->to != ends[i]) // move ants while dont reach local end
				{
					move_one_ant(edge, &output, edge->to->counter, edge->to->wrap->name);
					edge = (t_edge *)edge->to->links->data;
				}
				if (((t_edge*)ends[i]->links->data)->to == mngr->start)
				{
					ends[i]->counter--;
					move_one_ant(edge, &output, cur_lem, edge->to->wrap->name);
					cur_lem++;
					if (ends[i]->counter == 0)
						ends[i] = edge->from;
				}
				else
				{
					move_one_ant(edge, &output, edge->to->counter, edge->to->wrap->name);
					ends[i] = edge->from == mngr->end ? NULL : edge->from;
				}
			}
			cur = cur->next;
		}
		output = ft_vecpush(output, "\n", 1);
	}
	return (output);
}

/*
** overall algorithm
*/

void		get_all_paths(t_mngr *mngr)
{
	int			i;
	t_vector	*output;

	set_weights(mngr);
//	ft_printf("{Green}weights set{eof}\n\n"); // TODO remove
	if ((i = suurballe(mngr)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
//	ft_printf("{Blue}dijkstra has %i runs{eof}\n\n", -i - 2);  // TODO remove
	clean_graph(mngr, i - 1);
//	ft_printf("{Green}graph cleaned{eof}\n\n"); // TODO remove
	if (!(output = ft_vecinit(1000 * mngr->ant_num * sizeof(char))))
		ultimate_exit(mngr, MALLOC_ERROR);
	output = move_lems(mngr, output, ft_lstlen(mngr->end->links));
	ft_printf("\n%s", (char*)output->data);
	ft_vecdel((void **)&output);
}
