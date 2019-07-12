/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:32:36 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/13 00:13:24 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define FT_HTABLE_MISC
#include "htable.h"
#include <stdarg.h>
#include "libft.h"

char	*default_key_to_str(void *key, t_keytype kt)
{
	if (kt == OTHER)
		return (NULL);
	else if (kt != STRING)
		return (ft_itoa((long)key));
	else
		return (key);
}

static void	set_htab_functions(t_htab *htab, char *(f)())
{
	if (f)
		htab->key_to_str = f;
	else
		htab->key_to_str = default_key_to_str;
	htab->isin = ft_htab_isin;
	htab->add = ft_htab_add;
	htab->get = ft_htab_get;
	htab->pop = ft_htab_pop;
	htab->rem = ft_htab_rem;
}

t_vector *put_in_table(t_htab *htab, char *key, void *data)
{
	int hsh;

	hsh = hash(key);
	if (!(htab->table = ft_vecput(htab->table, hsh % htab->count, key, data)))
	{
		ft_htab_free(htab);
		return (NULL);
	}
	htab->count++;
}

t_htab	*ft_htab_init(char *(f)(void*), t_keytype kt, int count, ...)
{
	va_list ap;
	t_htab	*ret;

	if (!(ret = malloc(sizeof(t_htab))))
		return (NULL);
	ft_bzero(ret, sizeof(t_htab));
	if (!(ret->table = ft_vecinit((sizeof(t_bucket) * count * 2))))
	{
		free(ret);
		return (NULL);
	}
	ret->count = 0;
	set_htab_functions(ret, f);
	va_start(ap, count);
	while (count--)
		if (!(ret->table = put_in_table(ret, ret->key_to_str(va_arg(ap, char*),
				kt), va_arg(ap, void*))))
		{
			ret = NULL;
			break ;
		}
	va_end(ap);
	return (ret);
}

