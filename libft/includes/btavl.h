/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btavl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 16:44:14 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/09 21:35:01 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTAVL_H
# define BTAVL_H
# include "libft.h"

typedef enum		e_avl_key_type
{
	NUM32,
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

void			ft_avlfixh(t_btavl *tr);
t_btavl			*ft_avlrr(t_btavl *tr);
t_btavl			*ft_avlrl(t_btavl *tr);
t_btavl			*ft_avlbal(t_btavl *tr);
int				ft_avl_keycmp(t_btavl *a, t_btavl *b, int (f)(void*, void*));
# endif

t_btavl			*ft_avlnew(void *data, void *key, size_t size, t_avl_k_t kt);
t_btavl			*ft_avlnew_nc(void *data, void *key, size_t size, t_avl_k_t kt);
unsigned char	ft_avlh(t_btavl *tr);
int				ft_avlbfact(t_btavl *node);
t_btavl			*ft_avlins(t_btavl *tr, t_btavl *node);
t_btavl			*ft_avlrem(t_btavl *tr, int key, void (*f)(void **));
t_btavl			*ft_avlfree(t_btavl *tr);
void			*ft_avlsearch(t_btavl *tr, void *key, int ret_d,
						int (f)(void*, void*));
t_btavl			*ft_avlmin(t_btavl *tr);
t_btavl			*ft_avlmax(t_btavl *tr);
t_vector		*ft_avltovec(t_btavl *tr, t_vector *vec);

#endif
