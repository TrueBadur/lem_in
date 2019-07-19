/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_rehash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:45:59 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/19 13:45:59 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_HTABLE_MISC
#include "htable.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;
	unsigned int	c;

	hash = 0;
	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return hash;
}

t_htab			*ft_htab_rehash(t_htab *htab, int side)
{
	side++;
	return (htab);
}
