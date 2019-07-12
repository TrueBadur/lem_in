/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vh_get_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:59:49 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/12 20:17:03 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu_hex.h"

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

t_elt	vh_get_room(t_mngr *mngr, char *line)
{
	t_node	*node;

	if ((node = malloc(sizeof(t_viznode))) == NULL)
		ultimate_exit(mngr, MALLOC_ERROR);
	ft_bzero(node, sizeof(t_viznode));
	if (!(node->name = get_node_name(line)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (ft_htable_isin(mngr->nodes, node->name, NULL))
	{
		free(node->name);
		free(node);
		return (ERROR);
	}
	if (!(mngr->nodes = ft_htab_insert(mngr->nodes, node->name, node)))
		ultimate_exit(mngr, MALLOC_ERROR);
	if (mngr->instr == START)
		mngr->start = node;
	if (mngr->instr == FINISH)
		mngr->end = node;
	mngr->instr = INSTR_NONE;
	return (ROOM);
}
