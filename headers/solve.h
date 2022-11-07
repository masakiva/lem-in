/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/07 17:36:42 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include <stdlib.h>
# include <stdio.h>

#define		ARRY_END	-42

typedef struct	s_board
{
	int		*board;
}				t_board;

typedef	struct	s_solve_room
{
	int		id;
	int		x;
	int		y;
	int		*links;
	int		links_size;
}				t_solve_room;

typedef struct	s_solve
{
	t_room			**map_room_ary;
	t_solve_room	*rooms;
	int				rooms_size;
	int				all_links_size;
	int				ant_size;
	int				start_id;
	int				end_id;

}				t_solve;

typedef struct	s_ek_edge
{
	int		rev;
	int		to;
	int		from;
	int		cap;
}				t_ek_edge;

typedef struct	s_ek_node
{
	int				id;
	t_ek_edge		*edges;
	int				edges_size;
}				t_ek_node;

typedef struct	s_ek_graph
{
	t_ek_node	*nodes;
	
	int			*used;

	int			nodes_size;
	int			edges_size;
	int			start_input_id;
	int			start_output_id;
	int			end_input_id;
	int			end_output_id;

	//t_ek_edge	*edges;
}				t_ek_graph;

void	solve(t_map *m);
void	print_data(t_map *m);
void	generate_graph(t_map *map, t_solve *s, t_ek_graph *g);
void	find_max_flow(t_map *map, t_solve *s, t_ek_graph *g);

#endif
