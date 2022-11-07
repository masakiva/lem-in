/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:46:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 20:38:56 by mvidal-a         ###   ########.fr       */
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
	else if (*line == 'L')
	{
		printf("input err room name cannot begin with a L%d\n", INPUT_ERR);
		machine->state = END;
	}
	else
		machine->state = ROOMNAME;
	return (line);
}

char*	roomname(t_state_machine* machine, char* line)
{
	if (isroom(line))
	{
		parse_room(line, machine->map);
		if (find_dup_roomname(machine->map->rooms,
					((t_room *)ft_lstlast(machine->map->rooms)->content)->name))
			printf("input err duplicate room name%d\n", INPUT_ERR);
		if (find_dup_roomcoord(machine->map->rooms,
					(t_room *)ft_lstlast(machine->map->rooms)->content))
			printf("input err duplicate room coordinates%d\n", INPUT_ERR);
	}
	else if (islink(line))
	{
		parse_link(line, machine->map);
		if (find_dup_link(machine->map->links,
					(t_link *)ft_lstlast(machine->map->links)->content))
			printf("input err duplicate link%d\n", INPUT_ERR);
	}
	else
		printf("input err unknown syntax%d\n", INPUT_ERR);
	machine->state = END;
	return (line);
}

char*	hash(t_state_machine* machine, char* line)
{
	printf("hash\n");
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
	printf("double hash\n");
	if (ft_strcmp(line, "start") == 0)
		machine->map->start_flag = TRUE;
	else if (ft_strcmp(line, "end") == 0)
		machine->map->end_flag = TRUE;
	else
		printf("input err unknown syntax after ##%d\n", INPUT_ERR);
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
			printf("STARTTTT\n");
			machine->map->start =
				((t_room *)ft_lstlast(machine->map->rooms)->content)->name;
			machine->map->start_flag = FALSE;
		}
		if (machine->map->end_flag == TRUE)
		{
			printf("ENDDDD\n");
			machine->map->end =
				((t_room *)ft_lstlast(machine->map->rooms)->content)->name;
			machine->map->end_flag = FALSE;
		}
	}
	else
		printf("input err ##start or ##end must be followed by room definition %d\n", INPUT_ERR);
	machine->state = END;
	return (line);
}

