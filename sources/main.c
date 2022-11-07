/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:46:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/07 12:15:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "parse.h"
#include "solve.h"
#include <stdio.h>

void	check_input(t_map* map)
{
	t_list*		rooms;
	t_list*		links;
	t_link*		cur_link;
	t_room*		cur_room;
	t_bool		room1_found;
	t_bool		room2_found;

	links = map->links;
	while (links != NULL)
	{
		cur_link = (t_link *)links->content;
		room1_found = FALSE;
		room2_found = FALSE;
		rooms = map->rooms;
		while (rooms != NULL)
		{
			cur_room = (t_room *)rooms->content;
			if (!room1_found && ft_strcmp(cur_link->room1, cur_room->name) == 0)
				room1_found = TRUE;
			else if (!room2_found
					&& ft_strcmp(cur_link->room2, cur_room->name) == 0)
				room2_found = TRUE;
			if (room1_found && room2_found)
				break ;
			rooms = rooms->next;
		}
		if (!room1_found || !room2_found)
			error_exit(UNKNOWN_LINK);
		links = links->next;
	}
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

	check_input(&map);

	//solve(&map);
	
	return (EXIT_SUCCESS);
}
