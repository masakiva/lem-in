/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/04 19:42:45 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "lem-in.h"
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

void	solve(t_map *m);
void	print_data(t_map *m);

#endif
