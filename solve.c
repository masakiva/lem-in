/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:33:11 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/04 18:28:29 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "solve.h"
#include "libft.h"
#include <stdio.h>

void	show_all_data(t_solve *s)
{
	int		i;

	i = 0;
	printf("--- show t_solve ---\n");
	while (i < s->rooms_size)
	{
		printf("id: %d", s->rooms[i].id);
		printf(" name: %d", s->map_room_ary[i]->id);
		printf("\n");
		i++;
	}
}

void	parse_data(t_solve *s, t_map *map)
{
	s->rooms_size = ft_lstsize(map->rooms);
	printf("room num %d\n", s->rooms_size);
	
	s->all_links_size = ft_lstsize(map->links);
	printf("links num %d\n", s->all_links_size);
}

void	create_rooms(t_solve *s, t_map *map)
{
	t_solve_room	new_room;
	t_list			*room_ptr;
	int				i;

	// t_map->t_room ary
	s->map_room_ary = malloc(sizeof(t_room *) * (s->rooms_size + 1));
	i = 0;
	room_ptr = map->rooms;
	while (i < s->rooms_size)
	{
		s->map_room_ary[i] = (t_room *)room_ptr->content;
		i++;
		room_ptr = room_ptr->next;
	}
	// t_solve_room ary
	s->rooms = malloc(sizeof(t_solve_room) * (s->rooms_size));
	i = 0;
	while (i < s->rooms_size)
	{
		new_room.id = i;
		new_room.x = s->map_room_ary[i]->x;
		new_room.y = s->map_room_ary[i]->y;
		s->rooms[i] = new_room;
		i++;
	}
}

void	solve(t_map *map)
{
	t_solve	s;

	parse_data(&s, map);
	create_rooms(&s, map);

	show_all_data(&s);
}
