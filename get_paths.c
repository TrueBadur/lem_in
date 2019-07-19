/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/19 23:20:23 by mbartole         ###   ########.fr       */
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
//	ft_printf("%s", s); // TODO print local movement of ant
	return (s);
}

/*
** calculate total number of ants for every path,
** write it down to /node->counter/ for start of path
** (in fact it's /mngr->start->child/s)
*/
// TODO delete inner edges from final graph
void		calc_ants(t_list *ends, t_node *start, int ants)
{
	t_list	*tmp;
	int 	max;
	int 	sum;

	max = 0;
	tmp = ends;
	while (tmp)
	{
		((t_node *) tmp->data)->counter = get_path_len((t_node *) tmp->data, start, 1);
		max = ((t_node *) tmp->data)->counter > max ? ((t_node *) tmp->data)->counter : max;
		tmp = tmp->next;
	}
	sum = 0;
	tmp = ends;
	while (tmp)
	{
		((t_node *) tmp->data)->counter = max - ((t_node *) tmp->data)->counter;
		sum += ((t_node *) tmp->data)->counter;
		print_node(((t_node *) tmp->data));
		tmp = tmp->next;
	}
	sum = ants - sum;
	ft_printf("sum %i\n", sum);
	tmp = ends;
	max = sum % ft_lstlen(ends); // ostatok
	sum = sum / ft_lstlen(ends); // po skolko v kazdoe
	ft_printf("v kazdoe %i, ostatok %i\n", sum, max);
	while (tmp)
	{
		((t_node *) tmp->data)->counter += sum;
		if (max > 0)
		{
			((t_node *) tmp->data)->counter += 1;
			max--;
		}
		print_node(((t_node *) tmp->data));
		tmp = tmp->next;
	}
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
// TODO change ends from array to list
//t_vector 		*move_lems(t_mngr *mngr, t_vector *output, t_list *ends, int size)
//{
//	int cur_lem;
//	int count;
//	t_list	*cur;
//	t_edge	*edge;
//	int		finishs[size];
////	int 	i;
//
//	ft_bzero(finishs, sizeof(int) * ft_lstlen(ends));
//	cur_lem = 1;
//	count = 1;
//	while (count)
//	{
//		i = -1;
//		cur = mngr->end->links;
//		count = 0;
//		while (++i < size)
//		{
//			if (finishs[i])
//				move_one_ant((t_edge *)cur->data, &output, finishs[i], mngr->end->wrap->name);
//			if (ends[i] && ++count)
//			{
//				edge = (t_edge *)cur->data;
//				if (edge->to->counter != 0)
//					finishs[i] = edge->to->counter;
//				else
//					while (edge->to->counter == 0)  // just pass
//						edge = ((t_edge *)edge->to->links->data);
//				while (edge->to != ends[i]) // move ants while dont reach local end
//				{
//					move_one_ant(edge, &output, edge->to->counter, edge->to->wrap->name);
//					edge = (t_edge *)edge->to->links->data;
//				}
//				if (((t_edge*)ends[i]->links->data)->to == mngr->start)
//				{
//					ends[i]->counter--;
//					move_one_ant(edge, &output, cur_lem, edge->to->wrap->name);
//					cur_lem++;
//					if (ends[i]->counter == 0)
//						ends[i] = edge->from;
//				}
//				else
//				{
//					move_one_ant(edge, &output, edge->to->counter, edge->to->wrap->name);
//					ends[i] = edge->from == mngr->end ? NULL : edge->from;
//				}
//			}
//			cur = cur->next;
//		}
//		output = ft_vecpush(output, "\n", 1);
//	}
//	return (output);
//}

/*
** overall algorithm
*/

void		get_all_paths(t_mngr *mngr)
{
	int			i;
	t_vector	*output;
	t_list		*ends;  // TODO change everywhere array to list


	set_weights(mngr);
	ft_printf("{Green}weights set{eof}\n\n"); // TODO print
	ends = NULL;
	if ((i = suurballe(mngr, &ends)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
	ft_printf("{Blue}dijkstra has %i runs{eof}\n\n", -i - 2);  // TODO print
	clean_graph(mngr, i - 1);
	ft_printf("{Green}graph cleaned{eof}\n\n"); // TODO print
	calc_ants(ends, mngr->start, mngr->ant_num);
	if (!(output = ft_vecinit(1000 * mngr->ant_num * sizeof(char))))
		ultimate_exit(mngr, MALLOC_ERROR);
//	output = move_lems(mngr, output, ends, ft_lstlen(ends));
	ft_printf("\n%s", (char*)output->data);
	ft_vecdel((void **)&output);
}
