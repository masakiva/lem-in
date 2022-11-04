/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:17 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/04 14:51:25 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
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
	else if (ft_isdigit(*line))
		machine->state = DIGIT;
	else if (*line == '\0')
		machine->state = END;
	else
	{
		printf("input err %d\n", INPUT_ERR);
		machine->state = END;
	}
	return (line);
}

int		isroom(char* line)
{
	while (ft_isdigit(*line)) // room number
		line++;
	if (*line == ' ')
	{
		line++;
		while (ft_isdigit(*line)) // x coord
			line++;
		if (*line == ' ')
		{
			line++;
			while (ft_isdigit(*line)) // y coord
				line++;
			if (*line == '\0')
				return (TRUE);
		}
	}
	return (FALSE);
}

int		islink(char* line)
{
	while (ft_isdigit(*line)) // first room
		line++;
	if (*line == '-')
	{
		line++;
		while (ft_isdigit(*line)) // second room
			line++;
		if (*line == '\0')
			return (TRUE);
	}
	return (FALSE);
}

int		parse_number(char** str)
{
	int		nb;

	while (ft_isspace(**str) || **str == '-')
		(*str)++;
	nb = 0;
	while (ft_isdigit(**str))
	{
		nb = nb * 10 + **str - '0';
		(*str)++;
	}

	return (nb);
}

void	parse_room(char* line, t_map* map)
{
	t_room*		new_room;
	t_list*		lst_elem;
	
	new_room = malloc(sizeof(t_room));
	if (new_room == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	new_room->id = parse_number(&line);
	new_room->x = parse_number(&line);
	new_room->y = parse_number(&line);

	lst_elem = ft_lstnew(new_room);
	if (lst_elem == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	ft_lstadd_back(&map->rooms, lst_elem);

	printf("ROOM no %d, x = %d, y = %d\n", new_room->id, new_room->x, new_room->y);
}

void	parse_link(char* line, t_map* map)
{
	t_link*		new_link;
	t_list*		lst_elem;
	
	new_link = malloc(sizeof(t_link));
	if (new_link == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	new_link->room1 = parse_number(&line);
	new_link->room1 = parse_number(&line);

	lst_elem = ft_lstnew(new_link);
	if (lst_elem == NULL)
		printf("malloc err %d\n", MALLOC_ERR);
	ft_lstadd_back(&map->rooms, lst_elem);

	printf("LINK between rooms %d and %d\n", new_link->room1, new_link->room2);
}

char*	digit(t_state_machine* machine, char* line)
{
	if (isroom(line))
	{
		printf("ROOM\n");
		parse_room(line, machine->map);
	}
	else if (islink(line))
	{
		printf("LINK\n");
		parse_link(line, machine->map);
	}
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
	{
		printf("START\n");
	}
	else if (ft_strcmp(line, "end") == 0)
		printf("END\n");
	else
		printf("input err %d\n", INPUT_ERR);
	machine->state = END;
	return (line);
}

void	extract_line_infos(char* line, t_map* map)
{
	static t_parse	process[NB_STATES - 1] = {character, digit, hash,
		double_hash};
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(t_state_machine));
	machine.map = map;
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
		printf("line = %s\n", line);
		free(line);
	}

	return (ret);
}

int		main(void)
{
	int		ret;
	t_map	map;

	ret = 1;
	while (ret == 1)
	{
		ret = parse_line(&map);
	}

	return (EXIT_SUCCESS);
}
