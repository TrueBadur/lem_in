/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:59:11 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/22 19:01:29 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

t_list	*ft_lstadd_ret(t_list *alst, t_list *new)
{
	if (!alst)
		return (new);
	if (!new)
		return (alst);
	new->next = alst;
	return (new);
}
