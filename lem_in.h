/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:46:43 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/05 17:46:43 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

struct s_node;

typedef struct	s_edge
{
	int				wgth;
	struct s_node	*from;
	struct s_node	*to;
}				t_edge;

typedef struct s_node
{
	int			wgth;
	char		*name;
	t_edge		**links;
}				t_node;

#endif //LEM_IN_LEM_IN_H
