/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 05:22:01 by mbartole          #+#    #+#             */
/*   Updated: 2019/10/10 01:02:12 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	max = sum % size;
	sum = sum / size;
	i = -1;
	while (++i < size)
	{
		ends[i]->counter += sum;
		if (max-- > 0)
			ends[i]->counter += 1;
		if (ends[i]->counter == 0 && (ends[i]->counter = 1))
			ends[size - 1]->counter--;
	}
}

/*
** overall algorithm
*/

void		do_all_job(t_mngr *mngr)
{
	int		i;
	int		size;
	t_list	*ends;

	ends = NULL;
	size = -FT_MIN2(ft_lstlen(mngr->start->links),\
	ft_lstlen(((t_edge *)mngr->end->links->data)->to->links)) - 1;
	if ((i = suurballe(mngr, &ends, size)) == -2)
		ultimate_exit(mngr, NO_PATHS_FOUND);
	ft_lstdel(&ends, NULL);
	clean_graph(mngr, i - 1);
	size = ft_lstlen(mngr->end->links);
	move_ants(mngr, size);
	write(STDOUT_FILENO, mngr->input->data, mngr->input->len);
}

void move_all_at_once(t_mngr *mngr)
{
	int i;

	i = 0;
	while (i++ < mngr->ant_num)
		add_ant_to_vec(mngr, i, mngr->end->wrap->name);
	write(STDOUT_FILENO, mngr->input->data, mngr->input->len);
	ultimate_exit(mngr, SUCCESS);
}

void add_ant_to_vec(t_mngr *mngr, int num, char *name)
{
	char *s;

	if (mngr->fancy > 0)
	{
		mngr->input = ft_vecpush(mngr->input, "\033[38;5;", 7);
		s = ft_itoa(num);
		mngr->input = ft_vecpush(mngr->input, s, ft_strlen(s));
		mngr->input = ft_vecpush(mngr->input, "m", 1);
	}
	mngr->input = ft_vecpush(mngr->input, "L", 1);
	s = ft_itoa(num);
	mngr->input = ft_vecpush(mngr->input, s, ft_strlen(s));
	free(s);
	mngr->input = ft_vecpush(mngr->input, "-", 1);
	mngr->input = ft_vecpush(mngr->input, name, ft_strlen(name));
	if (!(mngr->input = ft_vecpush(mngr->input, " ", 1)))
		ultimate_exit(mngr, MALLOC_ERROR);
}