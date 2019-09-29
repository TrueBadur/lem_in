/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pque.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:43:51 by mbartole          #+#    #+#             */
/*   Updated: 2019/09/28 20:15:17 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUE_H
# define PQUE_H

# include "libft.h"

typedef struct	s_pque
{
	void		*data;
	int			priority;
}				t_pque;

void			*push_que(t_vector *vec, void *data, int priority);
t_pque			pop_que(t_vector *vec);

#endif
