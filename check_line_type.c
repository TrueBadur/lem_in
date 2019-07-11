/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:37:45 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/07/11 15:53:04 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int isvalidroomsymb(char c)
{
	return (c != '-' && !ft_isspace(c) && ft_isprint(c));
}

static int	islink(char *line)
{
	char f;

	f = 1;
	if (*line == 'L' || *line == '#')
		return (0);
	while(*line != '\0')
	{
		if (*line == '-' && f && !(*(line + 1) == 'L' || *(line + 1) == '#'))
			f = 0;
		else if (!isvalidroomsymb(*line))
			return (0);
		line++;
	}
	return (1);
}


static int 	isroom(char *lin)
{
	int	f;

	f = 2;
	if (*lin == 'L' || *lin == '#')
		return (0);
	while(*lin != '\0')
	{
		if (*lin == ' ' && *(lin + 1) == ' ')
		{
			lin++;
			continue ;
		}
		if (*lin == ' ' && f)
			f--;
		else if (f != 2 ? !ft_isdigit(*lin) : !(isvalidroomsymb(*lin)))
			return (0);
		lin++;
	}
	return (1);
}

t_elt		check_line_type(char *line)
{
	if (*line == '#')
		return (*(line + 1) == '#' ? INSTRUCTION : COMMENT);
	else if (ft_isnumeric(line))
		return (ANT_N);
	else if (islink(line))
		return (LINK);
	else if (isroom(line))
		return (ROOM);
	return (ERROR);
}
