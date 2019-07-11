/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:11:10 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/11 18:13:11 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

char	*get_node_name(char *line)
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

t_elt	get_room(t_mngr *mngr, char *line)
{
	t_node	*node;

	if ((node = malloc(sizeof(t_node))) == NULL)
		ultimate_exit(mngr, MALLOC_ERROR);
	ft_bzero(node, sizeof(t_node));
	if (!(node->name = get_node_name(line)))
		ultimate_exit(mngr, MALLOC_ERROR);
	node->counter = -1;
	if (ft_avlsearch(mngr->all_rooms, node->name, 0, NULL))
	{
		free(node->name);
		free(node);
		return (ERROR);
	}
	if (!(mngr->all_rooms = ft_avlins(mngr->all_rooms, ft_avlnew_nc(node,
			node->name,	sizeof(t_node),	STRING), NULL)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (mngr->instr == START)
		mngr->start = node;
	if (mngr->instr == FINISH)
		mngr->end = node;
	mngr->instr = INSTR_NONE;
	return (ROOM);
}
