/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:56:33 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/12 15:56:33 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helper.h"

t_mlx	*ft_mlx_init(char *main_wndw_name)
{
	t_mlx	*mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->interval = SPEED;
	mlx->pause = 0;
	mlx->active = 0;
	mlx->win_ptr = mlx_new_window(mlx->mlx, W_WIDTH, W_HEIGHT, main_wndw_name);
	return (mlx);
}
