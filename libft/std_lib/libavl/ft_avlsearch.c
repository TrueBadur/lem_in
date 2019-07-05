/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avlsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:43:37 by ehugh-be          #+#    #+#             */
/*   Updated: 2018/12/06 18:48:32 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btavl.h"

t_btavl	*ft_avlmin(t_btavl *tr)
{
	while (tr->left)
		tr = tr->left;
	return (tr);
}

t_btavl	*ft_avlmax(t_btavl *tr)
{
	while (tr->right)
		tr = tr->right;
	return (tr);
}

/*
** @param tr - tree to search through
** @param key - what key to find in tree
** @param ret_d - specifies what to return: data or node assosiated with key
** @return - if key is found then return ret_d assosiated with this key, NULL
** otherwise
*/

void	*ft_avlsearch(t_btavl *tr, int key, int ret_d)
{
	if (!tr)
		return (NULL);
	if (tr->key == key)
		return (ret_d ? tr->data : tr);
	if (key < tr->key)
		return (ft_avlsearch(tr->left, key, ret_d));
	else
		return (ft_avlsearch(tr->right, key, ret_d));
}
