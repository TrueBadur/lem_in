/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:58:51 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/07 21:49:21 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_ants_num(t_mngr *mngr, char *line)
{
	char *tmp;

	tmp = line;
	mngr->ant_num = ft_atoi_m((const char **)&line);
	if (mngr->ant_num > 0 && *line == '\0')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	ultimate_exit(mngr);
	return (0);
}

void get_room(t_mngr *mngr, char *line)
{

}
void get_link(t_mngr *mngr, char *line)
{

}

t_elt	check_line_type(t_mngr * mngr, char *line)
{
	return (ERROR);
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
		type = check_line_type(mngr, line);
		if (type == LINK)
			get_link(mngr, line);
		else if (type == ROOM)
			get_room(mngr, line);
		else if (type == INSTRUCTION)
			get_instruction(mngr, line);
		else if (type == ANT_N)
			get_ants_num(mngr, line);
		else if (type == ERROR)
			break ;
	}
}

