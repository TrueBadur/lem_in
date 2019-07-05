/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:12:33 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/05 18:22:08 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int main(int argc, char **argv)
{
	t_mngr *mngr;

	mngr = init_mngr(); //TODO
	if (argc > 1)
		parse_flags(argc, argv, mngr); //TODO
	parse_input(mngr); //TODO
	make_magic(mngr); //TODO
	print_solution(mngr); //TODO
	return (0);
}
