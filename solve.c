/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:33:11 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/04 20:53:37 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "solve.h"
#include "libft.h"
#include <stdio.h>

void	show_all_data(t_solve *s)
{
	int		i;
	int		j;

	i = 0;
	printf("--- show t_solve ---\n");
	while (i < s->rooms_size)
	{
		printf("room => ");
		printf("id: %d", s->rooms[i].id);
		printf(" name: %s", s->map_room_ary[i]->name);
		j = 0;
		printf(" link(id): ");
		while (j < s->rooms[i].links_size)
		{
			printf("%d, ", s->rooms[i].links[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int		find_index_by_name(t_solve *s, char *room_name)
{
	int		i;

	i = 0;
	while (i < s->rooms_size)
	{
		if (ft_strcmp(s->map_room_ary[i]->name, room_name) == 0)
			return i;
		i++;
	}
	return i;
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
		new_room.links = NULL;
		new_room.links_size = 0;
		s->rooms[i] = new_room;
		i++;
	}
}

void	set_link(t_solve *s, t_map *map)
{
	t_list	*link_ptr;
	int		room1;
	int		room2;
	int		i;

	//get number of links in each room
	link_ptr = map->links;
	while (link_ptr)
	{
		room1 = find_index_by_name(s, ((t_link*)link_ptr->content)->room1);
		room2 = find_index_by_name(s, ((t_link*)link_ptr->content)->room2);
		printf("link1: [%d] link2: [%d]\n", room1, room2);
		s->rooms[room1].links_size++;
		s->rooms[room2].links_size++;
		link_ptr = link_ptr->next;
	}

	//malloc links 
	i = 0;
	while (i < s->rooms_size)
	{
		s->rooms[i].links = malloc(sizeof(int) * s->rooms[i].links_size);
		s->rooms[i].links_size = 0;
		i++;
	}

	//submit links 
	link_ptr = map->links;
	while (link_ptr)
	{
		//find link
		room1 = find_index_by_name(s, ((t_link*)link_ptr->content)->room1);
		room2 = find_index_by_name(s, ((t_link*)link_ptr->content)->room2);
		//add link
		s->rooms[room1].links[s->rooms[room1].links_size] = room2;
		s->rooms[room2].links[s->rooms[room2].links_size] = room1;
		//inc link_size
		s->rooms[room1].links_size++;
		s->rooms[room2].links_size++;
		link_ptr = link_ptr->next;
	}
}

void	solve(t_map *map)
{
	t_solve	s;

	parse_data(&s, map);
	create_rooms(&s, map);
	set_link(&s, map);

	show_all_data(&s);
}
