/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/06 18:04:02 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include <stdlib.h>

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

}				t_solve;

typedef struct	s_ek_edge
{
	int		rev;
	int		to;
	int		cap;
}				t_ek_edge;

typedef struct	s_ek_node
{
	int		id;
	int		*edges;
}				t_ek_node;

typedef struct	s_ek_grapth
{
	t_ek_node	*nodes;
	//t_ek_edge	*edges;
}				t_ek_grapth;

void	solve(t_map *m);
void	print_data(t_map *m);

#endif
