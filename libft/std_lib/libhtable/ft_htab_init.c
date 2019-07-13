/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htab_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:32:36 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/13 17:21:34 by ehugh-be         ###   ########.fr       */
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

t_list *get_lst_from_table(t_htab *htab, size_t pos)
{
	if (((t_list*)(htab->table->data + pos)))
		return ((t_list*)(htab->table->data + pos));
	else
		return (NULL);
}

#define HTABLE_NUMEL (htab->table->cap / sizeof(t_bucket))

t_vector *put_in_table(t_htab *htab, char *key, void *data)
{
	int pos;
	t_list *lst;
	t_bucket bckt;

	pos = hash(key) % HTABLE_NUMEL;
	bckt.key = key;
	bckt.data = data;
	lst = get_lst_from_table(htab, pos);
	ft_lstadd(&lst, ft_lstnew(&bckt, sizeof(t_bucket)));
	if (!(htab->table = ft_vecput(htab->table, pos, sizeof(t_list*), &lst)))
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
	if (!(ret->table = ft_vecinit((sizeof(t_list*) * count * 4))))
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

int		ft_htab_isin(t_htab * htab, void *key, t_keytype kt)
{
	t_list	*lst;
	char 	*k;

	k = htab->key_to_str(key, kt);
	lst = get_lst_from_table(htab, hash(k));
	while(lst)
	{
		if (ft_strcmp(((t_bucket*)lst->data)->key, k) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

