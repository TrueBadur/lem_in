/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pque.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:43:51 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/11 14:54:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUE_H
# define PQUE_H

# include "libft.h"

typedef struct	s_pque
{
	void		*data;
	t_int2		priority;
}				t_pque;

void			*push_que(t_vector *vec, void *data, t_int2 priority);
t_pque			pop_que(t_vector *vec);
int ft_int2lt(t_int2 a, t_int2 b);
t_int2 ft_int2_min(t_int2 a, t_int2 b);
int ft_int2gt(t_int2 a, t_int2 b);
int ft_int2eq(t_int2 a, t_int2 b);

#endif
