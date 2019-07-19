/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:32:36 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/19 17:32:24 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_HTABLE_MISC
#include "htable.h"
#include <stdarg.h>

static void	set_htab_functions(t_htab *htab)
{
	htab->isin = ft_htab_isin;
	htab->add = ft_htab_add;
	htab->get = ft_htab_get;
	htab->pop = ft_htab_pop;
	htab->rem = ft_htab_rem;
	htab->next = ft_htab_generator;
}

t_htab		*ft_htab_init(int count, ...)
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
