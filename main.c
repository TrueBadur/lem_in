/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:12:33 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/10 18:29:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_mngr	*init_mngr(void)
{
	t_mngr *ret;

	if (!(ret = malloc(sizeof(t_mngr))))
		return (NULL);
	ft_bzero(ret, sizeof(t_mngr));
	ret->max_lt = LT_NONE;
	ret->ant_num = -1;
	ret->instr = INSTR_NONE;
	return (ret);
}

//TODO remove placeholder
void	ultimate_exit(t_mngr **mngr)
{
	*mngr = NULL;
	exit(1);
}

int main(int argc, char **argv)
{
	t_mngr *mngr;

	if (!(mngr = init_mngr()))
		ultimate_exit(NULL);//TODO
	argc += 0;
	argv += 0;
//	if (argc > 1)
//		parse_flags(argc, argv, mngr); //TODO
	parse_input(mngr); //TODO
	get_all_paths(mngr);
//	print_solution(mngr); //TODO
//	return (0);

}
