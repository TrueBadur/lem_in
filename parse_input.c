/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:58:51 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/09/28 19:04:03 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		type = get_link(mngr, line);
	else if (type == ROOM)
		type = get_room(mngr, line);
	else if (type == INSTRUCTION)
		get_instruction(mngr, line);
	else if (type == ANT_N)
		mngr->ant_num = ft_atoi(line);
	if (!(type == ERROR))
	{
		ft_string_push_back_s(&mngr->input, line);
		type = ft_string_push_back(&mngr->input, '\n') == 1 ? type : ERROR;
	}
	return (type);
}

void parse_input(t_mngr *mngr)
{
	char	*line;
	char	*tmp;
	t_elt	type;

	while(get_next_line(STDIN_FILENO, &line) > 0)
	{
		tmp = line;
		line = ft_strtrim(line);
		free(tmp);
		type = check_line_type(line);
		if (type < mngr->max_lt)
			type = ERROR;
		else if (type > mngr->max_lt && type < COMMENT)
			mngr->max_lt = type;
		type = parse_by_type(mngr, line, type);
		free(line);
		if (type == ERROR)
			break ;
	}
	if (!mngr->start || !mngr->end || mngr->ant_num < 0)
		ultimate_exit(mngr, NOT_ENOUGH_DATA);
	write(STDOUT_FILENO, mngr->input->data, mngr->input->len);
}
