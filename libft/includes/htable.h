/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:22:47 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/13 00:13:24 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
#define HTABLE_H

#include "t_vec.h"
#include "libft.h"

#ifndef FT_KEY_TYPE
#define FT_KEY_TYPE

typedef enum		e_key_type
{
	B_32,
	B_64,
	STRING,
	OTHER
}					t_keytype;
#endif

typedef struct	s_bucket
{
	char	*key;
	t_list	*lst;
}				t_bucket;

typedef struct	s_htable t_htab;

struct s_htable
{
	t_vector	*table;
	int			count;
	void		*(*get)(t_htab*, void*, t_keytype);
	int 		(*isin)(t_htab*, void*, t_keytype);
	t_htab		*(*add)(t_htab*, void *, t_keytype);
	void		*(*pop)(t_htab**, void*, t_keytype);
	t_htab		*(*rem)(t_htab*, void*, t_keytype);
	char		*(*key_to_str)(void*, t_keytype);
};

#ifdef FT_HTABLE_MISC
float	ft_ht_get_load_factor(t_htab *htab);
int		hash(char *key);
#endif

/* init with key aka char*, value aka void* */
//TODO write help
t_htab	*ft_htab_init(char *(f)(void*), t_keytype kt, int count, ...);
int		ft_htab_isin(t_htab *htab, void *key, t_keytype kt);
t_htab	*ft_htab_add(t_htab *htab, void *key, t_keytype kt);
void	*ft_htab_pop(t_htab **htab, void *key, t_keytype kt);
void	*ft_htab_get(t_htab *htab, void *key, t_keytype kt);
t_htab	*ft_htab_rem(t_htab *htab, void *key, t_keytype kt);
void	ft_htab_free(t_htab *htab);

#endif //LEM_IN_HTABLE_H

