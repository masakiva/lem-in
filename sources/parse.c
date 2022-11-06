/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:17 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 18:42:56 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <unistd.h>
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
		printf("input err %d\n", INPUT_ERR);
		machine->state = END;
	}
	else
		machine->state = ROOMNAME;
	return (line);
}

int		isroom(char* line)
{
	while (*line != ' ' && *line != '-' && *line != '\0') // room name
		line++;
	if (*line == ' ')
	{
		line++;
		if (ft_isdigit(*line))
		{
			while (ft_isdigit(*line)) // x coord
				line++;
			if (*line == ' ')
			{
				line++;
				if (ft_isdigit(*line))
				{
					while (ft_isdigit(*line)) // y coord
						line++;
					if (*line == '\0')
						return (TRUE);
				}
			}
		}
	}
	return (FALSE);
}

int		islink(char* line)
{
	while (*line != ' ' && *line != '-' && *line != '\0') // first room
		line++;
	if (*line == '-')
	{
		line++;
		while (*line != ' ' && *line != '-' && *line != '\0') // second room
			line++;
		if (*line == '\0')
			return (TRUE);
	}
	return (FALSE);
}

int		parse_number(char** str)
{
	int		nb;

	if (**str == ' ')
		(*str)++;
	nb = 0;
	while (ft_isdigit(**str))
	{
		nb = nb * 10 + **str - '0';
		(*str)++;
	}
	return (nb);
}

char*	parse_roomname(char** str)
{
	size_t	name_len;
	char*	name;

	name_len = 0;
	while ((*str)[name_len] != ' '
			&& (*str)[name_len] != '-'
			&& (*str)[name_len] != '\0')
		name_len++;
	name = ft_substr(*str, 0, name_len);
	if (name == NULL)
		return (NULL);
	*str += name_len;
	return (name);
}

void	parse_room(char* line, t_map* map)
{
	t_room*		new_room;
	t_list*		lst_elem;
	
	new_room = malloc(sizeof(t_room));
	if (new_room == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	new_room->name = parse_roomname(&line);
	if (new_room->name == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	new_room->x = parse_number(&line);
	new_room->y = parse_number(&line);

	lst_elem = ft_lstnew(new_room);
	if (lst_elem == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	ft_lstadd_back(&map->rooms, lst_elem);

	printf("ROOM name %s, x = %d, y = %d\n", new_room->name, new_room->x, new_room->y);
}

void	parse_link(char* line, t_map* map)
{
	t_link*		new_link;
	t_list*		lst_elem;
	
	new_link = malloc(sizeof(t_link));
	if (new_link == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	new_link->room1 = parse_roomname(&line);
	if (new_link->room1 == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	if (*line == '-')
		line++;
	new_link->room2 = parse_roomname(&line);
	if (new_link->room2 == NULL)
		printf("malloc err %d\n", MALLOC_ERR);

	lst_elem = ft_lstnew(new_link);
	if (lst_elem == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	ft_lstadd_back(&map->links, lst_elem);

	printf("LINK between rooms %s and %s\n", new_link->room1, new_link->room2);
}

char*	roomname(t_state_machine* machine, char* line)
{
	if (isroom(line))
		parse_room(line, machine->map);
	else if (islink(line))
		parse_link(line, machine->map);
	else
		printf("input err %d\n", INPUT_ERR);
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
		printf("input err %d\n", INPUT_ERR);
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
		printf("input err %d\n", INPUT_ERR);
	machine->state = END;
	return (line);
}

void	extract_line_infos(char* line, t_map* map)
{
	static t_parse	process[NB_STATES - 1] = {character, roomname, hash,
		double_hash, start_end_line};
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(t_state_machine));
	machine.map = map;
	if (map->start_flag == TRUE || map->end_flag == TRUE)
		machine.state = START_END_LINE;
	while (machine.state != END)
	{
		line = process[machine.state](&machine, line);
	}
}

int		parse_line(t_map* map)
{
	char*	line;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &line);
	if (ret == ERROR)
		printf("gnl err %d\n", GNL_ERR);
	else
	{
		extract_line_infos(line, map);
		free(line);
	}

	return (ret);
}
