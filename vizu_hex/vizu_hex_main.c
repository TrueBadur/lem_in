/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizu_hex_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:59:13 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/12 16:58:44 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu_hex.h"

void	init_mngr(t_mngr *mngr)
{
	ft_bzero(mngr, sizeof(t_mngr));
	mngr->nodes = ft_vecinit(sizeof(t_viznode *) * START_NODES);
	mngr->mlx = ft_mlx_init("Lem_in");
}

int main(void)
{
	t_mngr mngr;

	init_mngr(&mngr);
	vh_parse_input(&mngr);
	prepare_farm(&mngr);
	mlx_hook(mngr.mlx->win_ptr, 2, 5, hook_keydwn, (void*)&mngr);
	mlx_hook(mngr.mlx->win_ptr, 17, (1L << 3), window_close, (void*)&mngr);
	mlx_loop_hook(mngr.mlx, viz_loop, (void*)&mngr);
	mngr.mlx->sleep = clock() + mngr.mlx->interval;
	//TODO parse input
	// parse input into SOME struct like avl or hash table depends on...
	// go through all nodes and assign them position on the screen and color
	// corresponding to number of nodes and their connections
	// make array of ants with "name" and color and parent node for each ant
	//TODO loops
	return (0);
}
