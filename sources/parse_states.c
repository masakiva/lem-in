/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:46:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/10 19:16:26 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

char*	character(t_state_machine* machine, char* line)
{
	if (*line == '#')
	{
		machine->state = HASH;
		line++;
	}
	else if (*line == '\0')
		machine->state = END;
	else if (machine->map->rooms == NULL && (ft_isdigit(*line) || *line == '-'))
		machine->state = NB_ANTS;
	else if (*line == 'L')
	{
		error_exit(BEGIN_WITH_L);
		machine->state = END;
	}
	else
		machine->state = ROOMNAME;
	return (line);
}

char*	nb_ants(t_state_machine* machine, char* line)
{
	if (ft_str_isnumber(line))
	{
		if (!ispositiveint(line))
			error_exit(POSITIVE_NB_ANTS);
		if (machine->map->nb_ants != 0)
			error_exit(DUP_NB_ANTS);
		machine->map->nb_ants = ft_atoi(line);
		machine->state = END;
	}
	else
		machine->state = ROOMNAME;
	return (line);
}

char*	roomname(t_state_machine* machine, char* line)
{
	if (machine->map->nb_ants == 0)
		error_exit(NB_ANTS_MANDATORY);
	if (isroom(line))
		parse_room(line, machine->map);
	else if (islink(line))
	{
		if (machine->map->rooms == NULL)
			error_exit(ROOMS_MANDATORY);
		if (machine->map->start == NULL || machine->map->end == NULL)
			error_exit(START_END_MANDATORY);
		parse_link(line, machine->map);
	}
	else
		error_exit(UNKNOWN_SYNTAX);
	machine->state = END;
	return (line);
}

char*	hash(t_state_machine* machine, char* line)
{
	if (*line == '#')
	{
		machine->state = DOUBLE_HASH;
		line++;
	}
	else // it's a comment
		machine->state = END;
	return (line);
}

char*	double_hash(t_state_machine* machine, char* line)
{
	if (machine->map->nb_ants == 0)
		error_exit(NB_ANTS_MANDATORY);
	if (ft_strcmp(line, "start") == 0)
	{
		if (machine->map->start != NULL)
			error_exit(DUP_START);
		machine->map->start_flag = TRUE;
	}
	else if (ft_strcmp(line, "end") == 0)
	{
		if (machine->map->end != NULL)
			error_exit(DUP_END);
		machine->map->end_flag = TRUE;
	}
	machine->state = END;
	return (line);
}

char*	start_end_line(t_state_machine* machine, char* line)
{
	if (isroom(line))
	{
		parse_room(line, machine->map);
		if (machine->map->start_flag == TRUE)
		{
			machine->map->start =
				((t_room *)ft_lstlast(machine->map->rooms)->content)->name;
			machine->map->start_flag = FALSE;
		}
		if (machine->map->end_flag == TRUE)
		{
			machine->map->end =
				((t_room *)ft_lstlast(machine->map->rooms)->content)->name;
			machine->map->end_flag = FALSE;
		}
	}
	else
		error_exit(START_END_ROOM_DEF);
	machine->state = END;
	return (line);
}

