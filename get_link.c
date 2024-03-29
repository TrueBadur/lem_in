/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:17:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/29 13:05:51 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*init_edge(t_wnode *from, t_wnode *to)
{
	t_edge *ret;

	if (!(ret = malloc(sizeof(t_edge))))
		return (NULL);
	ret->wgth = 1;
	ret->from = &(from->out);
	ret->to = &(to->in);
	ret->was_rev = 0;
	return (ret);
}

void	get_node_avl(t_mngr *mngr, char *line, t_wnode **from, t_wnode **to)
{
	char	**link;
	char	**tmp;

	link = ft_strsplit(line, '-');
	*from = ft_avlsearch(mngr->all_rooms, link[0], 1, NULL);
	*to = ft_avlsearch(mngr->all_rooms, link[1], 1, NULL);
	tmp = link;
	while (*link)
	{
		free(*link);
		link++;
	}
	free(tmp);
}

void	deal_with_links(t_wnode *from, t_wnode *to, t_edge *edg_f,
		t_edge *edg_t)
{
	t_node	*f_out;
	t_node	*t_out;

	f_out = &(from->out);
	t_out = &(to->out);
	ft_lstadd(&f_out->links, ft_lstnew(edg_f, sizeof(t_edge)));
	ft_lstadd(&t_out->links, ft_lstnew(edg_t, sizeof(t_edge)));
}

t_elt	get_link(t_mngr *mngr, char *line)
{
	t_edge	*edg_t;
	t_edge	*edg_f;
	t_wnode	*from;
	t_wnode	*to;

	get_node_avl(mngr, line, &from, &to);
	if (!from || !to)
		return (ERROR);
	if (!(edg_f = init_edge(from, to)) ||
	!(edg_t = init_edge(to, from)))
	{
		free(edg_f);
		return (ERROR);
	}
	deal_with_links(from, to, edg_f, edg_t);
	free(edg_f);
	free(edg_t);
	return (LINK);
}
