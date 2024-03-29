/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:11:10 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/29 13:08:16 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			*get_node_name(char *line)
{
	char	*ret;
	int		i;

	i = ft_strchr(line, ' ') - line;
	if (!(ret = malloc(i + 1)))
		return (NULL);
	ft_strncpy(ret, line, i);
	ret[i] = '\0';
	return (ret);
}

static t_elt	setup_node(t_mngr *mngr, t_wnode *node, char *line)
{
	t_edge *ed;

	if (!(node->name = get_node_name(line)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (ft_avlsearch(mngr->all_rooms, node->name, 0, NULL))
	{
		free(node->name);
		free(node);
		return (ERROR);
	}
	node->in.wrap = node;
	node->out.wrap = node;
	node->in.tmp_label = INT32_MAX;
	node->out.tmp_label = INT32_MAX;
	if (!(ed = malloc(sizeof(t_edge))))
		ultimate_exit(mngr, MALLOC_ERROR);
	ed->wgth = 1;
	ed->from = &(node->in);
	ed->to = &(node->out);
	ed->was_rev = 0;
	ft_lstadd(&node->in.links, ft_lstnew(ed, sizeof(t_edge)));
	free(ed);
	return (ROOM);
}

t_elt			get_room(t_mngr *mngr, char *line)
{
	t_wnode	*node;

	if ((node = ft_memalloc(sizeof(t_wnode))) == NULL)
		ultimate_exit(mngr, MALLOC_ERROR);
	if (setup_node(mngr, node, line) == ERROR)
		return (ERROR);
	if (!(mngr->all_rooms = ft_avlins(mngr->all_rooms, ft_avlnew_nc(node,
			node->name, sizeof(t_wnode), STRING), NULL)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (mngr->instr == START)
		mngr->start = &(node->out);
	if (mngr->instr == FINISH)
		mngr->end = &(node->in);
	mngr->instr = INSTR_NONE;
	return (ROOM);
}
