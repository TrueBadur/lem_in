/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:54:40 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/11 19:16:42 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_node(void *node)
{
	t_wnode	*nd;

	nd = (t_wnode*)node;
	ft_lstdel(&(nd->in.links), NULL);
	ft_lstdel(&(nd->out.links), NULL);
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

