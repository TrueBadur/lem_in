/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_avltovec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:47:09 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/24 16:37:47 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btavl.h"

/*
** Gets all keys in the given tree and stores them in given vector.
** If it's impossible to allocate memory er value set to 1, so it has to be set
** to 0 before function execution, and NULL is returned.
** Inorder traversion is used to get keys.
** @param tr - t_btavl tree to get keys from.
** @param vec - t_vector to store key values, has to be previously initialised
** @param er - pointer to int, has to be 0 prior to evaluation this function
** in case of error will be set to 1. It's indicator of failure, because
** function may return NULL in case if given tree is empty
** @return - t_vector - vector with all keys of the given tree. Even though
** t_vector is given as argument to function it may be replaced with new value
** during growing of vector so use the returned value.
*/

t_vector	*ft_avlkeystovec(t_btavl *tr, t_vector *vec, int *er)
{
	if (!tr || !vec || *er)
		return (NULL);
	if (tr->left)
		if (!(vec = ft_avlkeystovec(tr->left, vec, er)) && (*er == 1))
			return (NULL);
	if (!(vec = ft_vecpush(vec, &tr->key, sizeof(int))) && (*er = 1))
		return (NULL);
	if (tr->right)
		if (!(vec = ft_avlkeystovec(tr->right, vec, er)) && (*er == 1))
			return (NULL);
	return (vec);
}

/*
** Gets all data from the given tree and copies it in given vector.
** If it's impossible to allocate memory er value set to 1, so it has to be set
** to 0 before function execution, and NULL is returned.
** Inorder traversion is used to get data.
** @param tr - t_btavl tree to get keys from.
** @param vec - t_vector to store key values, has to be previously initialised
** @param er - pointer to int, has to be 0 prior to evaluation this function
** in case of error will be set to 1. It's indicator of failure, because
** function may return NULL in case if given tree is empty
** @return - t_vector - vector with copy of all data of the given tree. Even
** though t_vector is given as argument to function it may be replaced with new
** value during growing of vector so use the returned value.
*/

t_vector	*ft_avldatatovec_deep(t_btavl *tr, t_vector *vec, int *er)
{
	if (!tr || !vec)
		return (NULL);
	if (tr->left)
		if (!(vec = ft_avldatatovec(tr->left, vec, er)) && (*er == 1))
			return (NULL);
	if (!(vec = ft_vecpush(vec, tr->data, sizeof(tr->size))) && (*er = 1))
		return (NULL);
	if (tr->right)
		if (!(vec = ft_avldatatovec(tr->right, vec, er)) && (*er == 1))
			return (NULL);
	return (vec);
}

/*
** Gets all pointers to data from the given tree and stores it in given vector.
** If it's impossible to allocate memory er value set to 1, so it has to be set
** to 0 before function execution, and NULL is returned.
** Inorder traversion is used to get data pointers.
** @param tr - t_btavl tree to get keys from.
** @param vec - t_vector to store key values, has to be previously initialised
** @param er - pointer to int, has to be 0 prior to evaluation this function
** in case of error will be set to 1. It's indicator of failure, because
** function may return NULL in case if given tree is empty
** @return - t_vector - vector with pointers to all datas of the given tree.
** Even though t_vector is given as argument to function it may be replaced with
** new value during growing of vector so use the returned value.
*/

t_vector	*ft_avldatatovec(t_btavl *tr, t_vector *vec, int *er)
{
	if (!tr || !vec || *er)
		return (NULL);
	if (tr->left)
		if (!(vec = ft_avldatatovec(tr->left, vec, er)) && (*er == 1))
			return (NULL);
	if (!(vec = ft_vecpush(vec, &tr->data, sizeof(void *))) && (*er = 1))
		return (NULL);
	if (tr->right)
		if (!(vec = ft_avldatatovec(tr->right, vec, er)) && (*er == 1))
			return (NULL);
	return (vec);
}

