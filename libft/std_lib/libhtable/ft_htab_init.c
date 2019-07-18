/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:32:36 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/18 22:22:04 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define FT_HTABLE_MISC
#include "htable.h"
#include <stdarg.h>
#include "libft.h"

unsigned long hash(char *str)
{
	unsigned long hash;
	unsigned int c;

	hash = 0;
	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

t_htab *ft_htab_rehash(t_htab *htab, int side)
{
	side++;
	return (htab);
}

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

t_list	*htab_rem_lst(t_list *lst, char *key, void (*f)(void*, size_t))
{
	t_list	*ret;

	if (!lst)
		return (NULL);
	if (!ft_strcmp(((t_bucket*)lst->data)->key, key))
	{
		ret = lst->next;
		ft_lstdelone(&lst, f);
		return (ret);
	}
	ret = lst;
	lst = lst->next;
	while (lst->next)
	{
		if (!ft_strcmp(((t_bucket*)lst->next->data)->key, key))
		{
			lst->next = lst->next->next;
			ft_lstdelone(&lst->next, f);
			return (ret);
		}
		lst = lst->next;
	}
	return (ret);
}

t_htab	*ft_htab_rem(t_htab *self, char *key, void (*f)(void*, size_t))
{
	size_t 	pos;

	pos = hash(key) % self->tabsize;
	if (!(self->table = ft_vecput(self->table, pos * sizeof(void*),
			sizeof(t_list*), &(void*){htab_rem_lst(htab_get_lst_strt(self, pos),
										 key, f)})))
	{
//		ft_htab_free(self);
		perror("ft_htab_add: vector reallocation failed");
		return (NULL);
	}
	self->count = self->count ? self->count - 1 : self->count;
	if (self->count && ((self->count - 1)) / (float)self->tabsize < 0.05)
		self = ft_htab_rehash(self, -1);
	return (self);
}

static void	set_htab_functions(t_htab *htab)
{
	htab->isin = ft_htab_isin;
	htab->add = ft_htab_add;
	htab->get = ft_htab_get;
	htab->rem = ft_htab_rem;
//	htab->pop = ft_htab_pop;
}

t_htab	*ft_htab_init(int count, ...)
{
	va_list ap;
	t_htab	*ret;

	if (!(ret = malloc(sizeof(t_htab))))
		return (NULL);
	ft_bzero(ret, sizeof(t_htab));
	if (!(ret->table = ft_vecinit((sizeof(t_list*) * count * 4))))
	{
		perror("Vector initialisation failed");
		free(ret);
		return (NULL);
	}
	ret->tabsize = ret->table->cap / sizeof(t_bucket*);
	ret->count = 0;
	set_htab_functions(ret);
	va_start(ap, count);
	while (count--)
		ret = ret->add(ret, va_arg(ap, void*), va_arg(ap, void*));
	va_end(ap);
	return (ret);
}
