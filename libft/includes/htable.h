/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htable.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:22:47 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/18 21:04:56 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTABLE_H
#define HTABLE_H

#include "t_vec.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

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
	void	*data;
}				t_bucket;

typedef struct	s_htable t_htab;

/**
 * add - is alias for ft_htab_add()
 * isin - is alias for ft_htab_isin()
 */

struct s_htable
{
	t_vector	*table;
	int			count;
	size_t		tabsize;
	void		*(*get)(t_htab*, char *key);
	int 		(*isin)(t_htab*, char *key);
	t_htab		*(*add)(t_htab *self, char *key, void *data);
	void		*(*pop)(t_htab**, char *key);
	t_htab		*(*rem)(t_htab*, char *key, void (*f)(void*, size_t));
};

#ifdef FT_HTABLE_MISC
float	ft_ht_get_load_factor(t_htab *htab);
unsigned long		hash(char *str);
t_list	*htab_get_lst(t_htab *htab, char *key);
t_list	*htab_get_lst_strt(t_htab *htab, size_t pos);
#endif

/* init with key aka char*, value aka void* */
//TODO write help
/**
 * Initialises htab with size 4 * count.
 * @param count
 * @param ...
 * @return
 */
t_htab	*ft_htab_init(int count, ...);
/**
** Checks if key is in htable.
** @param self - htable to check in
** @param key - key to check for
** @return - 1 in case if key already in htable or 0 if not.
*/
int 	ft_htab_isin(t_htab *self, char *key);
/**
** Add or replace key-value pair in htab. Be careful: it will replace data if
** key already in array, what may cause leaks.
** @param self - (t_htab*) Table in which to add key-value pair.
** @param key - (char*) String that will be the key of the given value
** @param data - (void*) value that will be stored in table
** @return - Return the same htab or NULL if something went wrong. errno set to
** corresponding value.
*/
t_htab *ft_htab_add(t_htab *self, char *key, void *data);
//TODO t_htab	*ft_htab_addwithfree();
void	*ft_htab_pop(t_htab **htab, char *key);
void	*ft_htab_get(t_htab *htab, char *key);
t_htab	*ft_htab_rem(t_htab *htab, char *key, void (*f)(void*, size_t));
void	ft_htab_free(t_htab *htab);

#endif //LEM_IN_HTABLE_H

