/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:48:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/19 13:48:21 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_HTABLE_MISC
#include "htable.h"

t_htab *ft_htab_add(t_htab *self, char *key, void *data)
{
	long		pos;
	t_list		*lst;
	t_bucket	bckt;
	char 		*tst;

	if (((self->count + 1)) / (float)self->tabsize > 0.75)
		self = ft_htab_rehash(self, 0);
	if ((lst = htab_get_lst(self, key)))
	{
		((t_bucket*)lst->data)->data = data;
		return (self);
	}
	bckt.data = data;
	bckt.key = key;
	pos = hash(bckt.key) % self->tabsize;
	lst = htab_get_lst_strt(self, pos);
	ft_lstadd(&lst, ft_lstnew(&bckt, sizeof(t_bucket)));
	tst = ((t_bucket*)lst->data)->key;
	if (!(self->table = ft_vecput(self->table, pos * sizeof(void*), sizeof(t_list*), &lst)))
	{
//		ft_htab_free(self);
		perror("ft_htab_add: vector reallocation failed");
		return (NULL);
	}
	self->tabsize = self->table->cap / sizeof(void*);
	self->count++;
	return (self);
}