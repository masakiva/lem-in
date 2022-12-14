/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:51:23 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 20:25:55 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

int		ft_str_isnumber(char* str)
{
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int		ispositiveint(char* str)
{
	size_t	i;

	if (str[0] == '-')
		return (FALSE);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 10)
		return (FALSE);
	if (i == 10 && str[0] > '2')
		return (FALSE);
	if (ft_atoi(str) < 1)
		return (FALSE);
	return (TRUE);
}

int		isroom(char* line)
{
	if (*line != ' ' && *line != '-' && *line != '\0')
	{
		while (*line != ' ' && *line != '-' && *line != '\0') // room name
			line++;
		if (*line == ' ')
		{
			line++;
			if (*line == '-')
				line++;
			if (ft_isdigit(*line))
			{
				while (ft_isdigit(*line)) // x coord
					line++;
				if (*line == ' ')
				{
					line++;
					if (*line == '-')
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
	}
	return (FALSE);
}

int		islink(char* line)
{
	if (*line != ' ' && *line != '-' && *line != '\0')
	{
		while (*line != ' ' && *line != '-' && *line != '\0') // first room
			line++;
		if (*line == '-')
		{
			line++;
			if (*line != ' ' && *line != '-' && *line != '\0')
			{
				while (*line != ' ' && *line != '-' && *line != '\0') // second room
					line++;
				if (*line == '\0')
					return (TRUE);
			}
		}
	}
	return (FALSE);
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

static t_bool	find_dup_roomname(t_list* rooms, char* name_to_compare)
{
	t_room*		cur_room;

	while (rooms != NULL)
	{
		cur_room = (t_room *)rooms->content;
		if (ft_strcmp(cur_room->name, name_to_compare) == 0)
			return (TRUE);
		rooms = rooms->next;
	}
	return (FALSE);
}

static t_bool	find_dup_roomcoord(t_list* rooms, t_room* room_to_compare)
{
	t_room*		cur_room;

	while (rooms != NULL)
	{
		cur_room = (t_room *)rooms->content;
		if (cur_room->x == room_to_compare->x
				&& cur_room->y == room_to_compare->y)
			return (TRUE);
		rooms = rooms->next;
	}
	return (FALSE);
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
	if (find_dup_roomname(map->rooms, new_room->name))
		error_exit(DUP_ROOMNAME);

	if (ft_isint(line) == FALSE)
		error_exit(COORD_INT_OVERFLOW);
	new_room->x = ft_atoi(line);
	line = skip_int(line);
	if (ft_isint(line) == FALSE)
		error_exit(COORD_INT_OVERFLOW);
	new_room->y = ft_atoi(line);
	line = skip_int(line);
	if (find_dup_roomcoord(map->rooms, new_room))
		error_exit(DUP_ROOMCOORD);

	lst_elem = ft_lstnew(new_room);
	if (lst_elem == NULL)
		error_exit(MALLOC_ERR);
	ft_lstadd_back(&map->rooms, lst_elem);
}

static t_bool	find_room(char* name, t_list* rooms)
{
	t_room*		cur_room;

	while (rooms != NULL)
	{
		cur_room = (t_room *)rooms->content;
		if (ft_strcmp(name, cur_room->name) == 0)
			return (TRUE);
		rooms = rooms->next;
	}
	return (FALSE);
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
	if (find_room(new_link->room1, map->rooms) == FALSE)
		error_exit(LINK_UNKNOWN_ROOMNAME);
	if (*line == '-')
		line++;
	new_link->room2 = parse_roomname(&line);
	if (new_link->room2 == NULL)
		error_exit(MALLOC_ERR);
	if (ft_strcmp(new_link->room1, new_link->room2) == 0)
		error_exit(LINK_SAME_ROOMNAMES);
	if (find_room(new_link->room2, map->rooms) == FALSE)
		error_exit(LINK_UNKNOWN_ROOMNAME);

	lst_elem = ft_lstnew(new_link);
	if (lst_elem == NULL)
		error_exit(MALLOC_ERR);
	ft_lstadd_back(&map->links, lst_elem);
}
