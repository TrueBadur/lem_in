/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vh_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:43:42 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/12 16:43:42 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizu_hex.h"

void get_instruction(t_mngr *mngr, char *line)
{
	if (ft_strcmp(line + 2, "start") == 0)
		mngr->instr = START;
	else if (ft_strcmp(line + 2, "end") == 0)
		mngr->instr = FINISH;
	else
		mngr->instr = INSTR_NONE;
}

static t_elt parse_by_type(t_mngr *mngr, char *line, t_elt type)
{
	if (type == LINK)
		type = vh_get_link(mngr, line);
	else if (type == ROOM)
		type = vh_get_room(mngr, line);
	else if (type == INSTRUCTION)
		get_instruction(mngr, line);
	else if (type == ANT_N)
		mngr->ant_num = ft_atoi(line);
	return (type);
}

void	vh_parse_input(t_mngr * mngr)
{
	char	*line;
	t_elt	type;

	while(get_next_line(STDIN_FILENO, &line) > 0)
	{
		type = check_line_type(line, 1);
		type = parse_by_type(mngr, line, type);
		free(line);
		if (type == ERROR)
			ultimate_exit(mngr, NOT_ENOUGH_DATA);
		if (type == EMPTY_LINE)
			return ;
	}
}

