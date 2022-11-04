/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:33:11 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/04 16:46:44 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "solve.h"
#include "libft.h"
#include <stdio.h>

void	parse_data(t_solve *s, t_map *map)
{
	s->rooms_num = ft_lstsize(map->rooms);
	printf("room num %d\n", s->rooms_num);
	
	s->all_links_num = ft_lstsize(map->links);
	printf("links num %d\n", s->all_links_num);

}

void	create_rooms(t_solve *s, t_map *map)
{
	t_solve_room	new_room;
	int				i;
	t_list			*room_ptr;

	s->rooms = malloc(sizeof(t_solve_room) * (s->rooms_num));
	i = 0;
	room_ptr = map->rooms;
	while (i < s->rooms_num)
	{
		new_room.id = i;
		new_room.x = ((t_room *)room_ptr->content)->x; 
		new_room.y = ((t_room *)room_ptr->content)->y;
		i++;
		room_ptr = room_ptr->next;
	}
}

void	solve(t_map *map)
{
	t_solve	s;

	parse_data(&s, map);
	create_rooms(&s, map);
}
