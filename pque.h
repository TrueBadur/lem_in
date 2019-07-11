/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pque.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:43:51 by mbartole          #+#    #+#             */
/*   Updated: 2019/07/07 23:36:35 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PQUE_H
#define PQUE_H

typedef struct s_pque
{
	void 			*data;
	int 			priority;
}				t_pque;

void	push_que(t_vector *vec, void *data, int priority);
t_pque	pop_que(t_vector *vec);

#endif
