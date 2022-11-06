/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:46:30 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 20:29:53 by mvidal-a         ###   ########.fr       */
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

t_bool	find_dup_roomname(t_list* rooms, char* name_to_compare)
{
	t_room*		cur_room;

	while (rooms != NULL)
	{
		cur_room = (t_room *)rooms->content;
		if (cur_room->name != name_to_compare
				&& ft_strcmp(cur_room->name, name_to_compare) == 0)
			return (TRUE);
		rooms = rooms->next;
	}
	return (FALSE);
}

t_bool	find_dup_link(t_list* links, t_link* link_to_compare)
{
	t_link*		cur_link;

	while (links != NULL)
	{
		cur_link = (t_link *)links->content;
		if (cur_link != link_to_compare)
		{
			if (ft_strcmp(cur_link->room1, link_to_compare->room1) == 0
					&& ft_strcmp(cur_link->room2, link_to_compare->room2) == 0)
				return (TRUE);
			else if (ft_strcmp(cur_link->room1, link_to_compare->room2) == 0
					&& ft_strcmp(cur_link->room2, link_to_compare->room1) == 0)
				return (TRUE);
		}
		links = links->next;
	}
	return (FALSE);
}

char*	roomname(t_state_machine* machine, char* line)
{
	if (isroom(line))
	{
		parse_room(line, machine->map);
		if (find_dup_roomname(machine->map->rooms,
					((t_room *)ft_lstlast(machine->map->rooms)->content)->name))
			printf("input err duplicate room name%d\n", INPUT_ERR);
	}
	else if (islink(line))
	{
		parse_link(line, machine->map);
		if (find_dup_link(machine->map->links,
					(t_link *)ft_lstlast(machine->map->links)->content))
			printf("input err duplicate room name%d\n", INPUT_ERR);
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

