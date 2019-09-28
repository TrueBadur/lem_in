/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:12:33 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/28 19:03:08 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_mngr	*init_mngr(void)
{
	t_mngr *ret;

	if (!(ret = ft_memalloc(sizeof(t_mngr))))
		return (NULL);
	ret->input = ft_vecinit(INPUT_VECTOR_SIZE);
	ret->max_lt = LT_NONE;
	ret->ant_num = -1;
	ret->instr = INSTR_NONE;
	return (ret);
}

int main(int argc, char **argv)
{
	t_mngr *mngr;

	if (!(mngr = init_mngr()))
		ultimate_exit(NULL, MALLOC_ERROR);//TODO
	argc += 0;
	argv += 0;
//	if (argc > 1)
//		parse_flags(argc, argv, mngr); //TODO
	parse_input(mngr); //TODO
//	test(mngr);
	do_all_job(mngr);
//	print_solution(mngr); //TODO
	ultimate_exit(mngr, SUCCESS);
}



