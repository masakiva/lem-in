/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/13 15:20:52 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include <stdlib.h>
# include <stdio.h>
# include "ft_queue.h"

#define		ARRY_END	-42

typedef	struct	s_solve_room
{
	int		id;
	int		x;
	int		y;
	int		*links;
	char	*name_ptr;
	int		links_size;
}				t_solve_room;



typedef struct	s_ek_edge
{
	int		rev;
	int		to;
	int		from;
	int		is_rev;
	int		cap;
}				t_ek_edge;

typedef struct	s_ek_node
{
	int				id;
	t_ek_edge		*edges;
	int				edges_size;
}				t_ek_node;

typedef struct	s_path
{
	int			*root;
	int			root_size;
	int			use_num;
}				t_path;

typedef struct	s_path_set
{
	t_path		**paths;
	int			paths_size;
}				t_path_set;

typedef struct	s_path_manager
{
	t_list		*path_set_list;
	int			path_set_list_size;

	t_path		*current_path;
	t_path_set	*current_path_set;
	int			turn;
}				t_path_manager;

typedef struct	s_ek_graph
{
	t_ek_node		*nodes;
	t_path_manager	path_manager;

	int			*root_buffer_begin;
	int			*root_buffer_end;
	
	int			*bfs_used;
	int			*bfs_node_from;
	int			*bfs_edge_from;

	int			nodes_size;
	int			edges_size;
	int			start_input_id;
	int			start_output_id;
	int			end_input_id;
	int			end_output_id;

	//t_ek_edge	*edges;
}				t_ek_graph;

typedef struct	s_ant
{
	int			path_position;
	int			id;
	int			start_turn;
	int			end_turn;
	t_path		*path;
}				t_ant;

typedef struct	s_ant_manager
{
	t_ant		*ants;
	t_list		*path_list;
	int			ants_count;
	int			ants_limit;
	int			turn;
}				t_ant_manager;

typedef struct	s_ans_ant
{
	int			id;
	int			room_id;
}				t_ans_ant;

typedef struct	s_ans_turn
{
	t_list	*ans_ants;
	int		turn;
}				t_ans_turn;

typedef struct	s_answer
{
	t_list		*ans_turns;	
	t_list		*currnt_turn;
}				t_answer;

typedef struct	s_solve
{
	t_room			**map_room_ary;
	t_solve_room	*rooms;
	t_ant_manager	ant_manager;
	t_answer		answer;
	int				rooms_size;
	int				all_links_size;
	int				ant_size;
	int				start_id;
	int				end_id;

}				t_solve;

void	solve(t_map *m);
void	print_data(t_map *m);
void	generate_graph(t_map *map, t_solve *s, t_ek_graph *g);
void	find_max_flow(t_map *map, t_solve *s, t_ek_graph *g);


//select_path_set
void	select_path_set(t_map *map, t_solve *s, t_ek_graph *g);

//flow ant
void	flow_ants(t_map *map, t_solve *s, t_ek_graph *g);
#endif
