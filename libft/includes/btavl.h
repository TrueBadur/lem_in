/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btavl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:44:14 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/24 16:20:53 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTAVL_H
# define BTAVL_H
# include "libft.h"
# define TO_AVL_KEY(x) ((void*)((long)(x)))

typedef enum		e_avl_key_type
{
	NUM32,
	NUM64,
	STRING,
	OTHER
}					t_avl_k_t;

typedef struct		s_btavl
{
	void			*data;
	size_t			size;
	void			*key;
	struct s_btavl	*left;
	struct s_btavl	*right;
	char			copy;
	t_avl_k_t		key_type;
	unsigned char	h;
}					t_btavl;

# ifdef FT_SOURCE_BTAVL
/* Internal functions not to be exposed to end-user */
void			ft_avlfixh(t_btavl *tr);
t_btavl			*ft_avlrr(t_btavl *tr);
t_btavl			*ft_avlrl(t_btavl *tr);
t_btavl			*ft_avlbal(t_btavl *tr);
int	ft_avl_keycmp(void *a, void *b, t_avl_k_t kt, int (f)(void*, void*));
# endif

/*-------------------------TREE NODE CREATION---------------------------------*/
t_btavl			*ft_avlnew(void *data, void *key, size_t size, t_avl_k_t kt);
t_btavl			*ft_avlnew_nc(void *data, void *key, size_t size, t_avl_k_t kt);

/*-------------------------MISCELLANEOUS--------------------------------------*/
unsigned char	ft_avlh(t_btavl *tr);
int				ft_avlbfact(t_btavl *node);

/*-------------------------NODE INSERTION-------------------------------------*/
t_btavl			*ft_avlins(t_btavl *tr, t_btavl *node, int (f)(void*, void*));

/*-------------------------REMOVING TREE AND NODES----------------------------*/
t_btavl			*ft_avlrem(t_btavl *tr, void *key, void (*f)(void **),
							  int (f_c)(void*, void*));
t_btavl			*ft_avlfree(t_btavl *tr);
t_btavl			*ft_avlfree_custom(t_btavl *tr, void (f)(void*));

/*-------------------------SEAECHING THE TREE---------------------------------*/
void			*ft_avlsearch(t_btavl *tr, void *key, int ret_d,
						int (f)(void*, void*));
t_btavl			*ft_avlmin(t_btavl *tr);
t_btavl			*ft_avlmax(t_btavl *tr);

/*-------------------------CONVERT TO VECTOR----------------------------------*/
/* Gets all keys from given tree to vector. Returns vector of keys or NULL.
** error set to 1 if something went wrong.
*/
t_vector		*ft_avlkeystovec(t_btavl *tree, t_vector *vector, int * error);

/* Gets copy of all data from given tree to vector. Returns vector of data or
** NULL. error set to 1 if something went wrong.
*/
t_vector		*ft_avldatatovec_deep(t_btavl *tree, t_vector *vector,
 int * error);

/* Gets pointers of all data from given tree to vector. Returns vector of
** pointers to data or NULL. error set to 1 if something went wrong.
*/
t_vector		*ft_avldatatovec(t_btavl *tree, t_vector *vector, int * error);


#endif
