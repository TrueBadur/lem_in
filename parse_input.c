/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:58:51 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/09 19:09:26 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



t_elt	get_link(t_mngr *mngr, char *line)
{

}

void get_instruction(t_mngr *mngr, char *line)
{

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
		free(line);
		if (type == ERROR)
			break ;
	}
	if (!isenoughdata(mngr))
		ultimate_exit(&mngr);
}

