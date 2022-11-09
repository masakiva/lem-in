/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:33:11 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/09 21:45:50 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "solve.h"
#include "libft.h"
#include "ft_queue.h"
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

	s->ant_size = 3;
}

void	create_rooms(t_solve *s, t_map *map)
{
	t_solve_room	new_room;
	t_list			*room_ptr;
	int				i;

	// t_map->t_room ary
	s->map_room_ary = malloc(sizeof(t_room *) * (s->rooms_size + 1));
	if (s->map_room_ary == NULL)
		error_exit(MALLOC_ERR);
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
	if (s->rooms == NULL)
		error_exit(MALLOC_ERR);
	i = 0;
	while (i < s->rooms_size)
	{
		new_room.id = i;
		new_room.x = s->map_room_ary[i]->x;
		new_room.y = s->map_room_ary[i]->y;
		new_room.name_ptr = s->map_room_ary[i]->name;
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
		if (s->rooms[i].links == NULL)
			error_exit(MALLOC_ERR);
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

void	set_start_and_end(t_map *map, t_solve *s)
{
	s->start_id = find_index_by_name(s, map->start);
	s->end_id = find_index_by_name(s, map->end);
}

void	solve(t_map *map)
{
	t_solve			s;
	t_ek_graph		graph;

	parse_data(&s, map);
	create_rooms(&s, map);
	set_link(&s, map);
	set_start_and_end(map, &s);
	show_all_data(&s);

	generate_graph(map, &s, &graph);
	find_max_flow(map, &s, &graph);
	select_path_set(map, &s, &graph);
}
