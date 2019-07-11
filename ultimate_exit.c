/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:54:40 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/11 18:12:31 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_node(void *node)
{
	t_node	*nd;
	t_list	*tmp;

	nd = (t_node*)node;
	while (nd->links)
	{
		tmp = nd->links;
		nd->links = nd->links->next;
		free(tmp->data);
		free(tmp);
	}
	free(nd->name);
	free(node);
}

void ultimate_exit(t_mngr *mngr, int exit_code)
{
	if (mngr)
	{
		ft_avlfree_custom(mngr->all_rooms, free_node);
		free(mngr);
	}
	if (exit_code != 0)
		ft_printf("ERROR");
	exit(exit_code);
}

