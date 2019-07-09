/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:58:51 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/09 20:34:01 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void get_instruction(t_mngr *mngr, char *line)
{
	if (ft_strcmp(line + 2, "start"))
		mngr->instr = START;
	else if (ft_strcmp(line + 2, "finish"))
		mngr->instr = FINISH;
	else
		mngr->instr = NONE;
}

void parse_input(t_mngr *mngr)
{
	char	*line;
	t_elt	type;

	while(get_next_line(STDIN_FILENO, &line) > 0)
	{
		type = check_line_type(line);
		if (type == LINK)
			get_link(mngr, line);
		else if (type == ROOM)
			type = get_room(mngr, line);
		else if (type == INSTRUCTION)
			get_instruction(mngr, line);
		else if (type == ANT_N)
			mngr->ant_num = ft_atoi(line);
		mngr->instr = NONE;
		free(line);
		if (type == ERROR)
			break ;
	}
	if (!mngr->start || !mngr->end)
		ultimate_exit(&mngr);
}

