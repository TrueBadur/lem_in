/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:17:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/10 17:06:52 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*init_edge(t_node *from, t_node *to)
{
	t_edge *ret;

	if (!(ret = malloc(sizeof(t_edge))))
		return NULL;
	ret->wgth = -1;
	ret->from = from;
	ret->to = to;
	return (ret);
}

void	get_node_avl(t_mngr *mngr, char *line, t_node **from, t_node **to)
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

t_elt	get_link(t_mngr *mngr, char *line)
{
	t_edge	*edg_t;
	t_edge	*edg_f;
	t_node	*from;
	t_node	*to;

	get_node_avl(mngr, line, &from, &to);
	if (!from || !to)
		return (ERROR);
	if (!(edg_f = init_edge(from, to)) || !(edg_t = init_edge(to, from)))
	{
		free(edg_f);
		return (ERROR);
	}
	edg_f->reverse = edg_t;
	edg_t->reverse = edg_f;
	ft_lstadd(&from->links, ft_lstnew(edg_f, sizeof(t_edge)));
	ft_lstadd(&to->links, ft_lstnew(edg_t, sizeof(t_edge)));
	free(edg_f);
	free(edg_t);
	return (LINK);
}
