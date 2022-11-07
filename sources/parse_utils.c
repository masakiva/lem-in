/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:51:23 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/07 11:57:13 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

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

static int		parse_number(char** str)
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

static char*	parse_roomname(char** str)
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
		error_exit(MALLOC_ERR);
	*str += name_len;
	return (name);
}

void	parse_room(char* line, t_map* map)
{
	t_room*		new_room;
	t_list*		lst_elem;
	
	new_room = malloc(sizeof(t_room));
	if (new_room == NULL)
		error_exit(MALLOC_ERR);
	new_room->name = parse_roomname(&line);
	if (new_room->name == NULL)
		error_exit(MALLOC_ERR);
	new_room->x = parse_number(&line);
	new_room->y = parse_number(&line);

	lst_elem = ft_lstnew(new_room);
	if (lst_elem == NULL)
		error_exit(MALLOC_ERR);
	ft_lstadd_back(&map->rooms, lst_elem);

	printf("ROOM name %s, x = %d, y = %d\n", new_room->name, new_room->x, new_room->y);
}

void	parse_link(char* line, t_map* map)
{
	t_link*		new_link;
	t_list*		lst_elem;
	
	new_link = malloc(sizeof(t_link));
	if (new_link == NULL)
		error_exit(MALLOC_ERR);
	new_link->room1 = parse_roomname(&line);
	if (new_link->room1 == NULL)
		error_exit(MALLOC_ERR);
	if (*line == '-')
		line++;
	new_link->room2 = parse_roomname(&line);
	if (new_link->room2 == NULL)
		error_exit(MALLOC_ERR);

	lst_elem = ft_lstnew(new_link);
	if (lst_elem == NULL)
		error_exit(MALLOC_ERR);
	ft_lstadd_back(&map->links, lst_elem);

	printf("LINK between rooms %s and %s\n", new_link->room1, new_link->room2);
}

