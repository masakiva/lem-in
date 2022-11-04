/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:35:31 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/04 16:41:35 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H

# include "lem-in.h"
# include <stdlib.h>

#define		ARRY_END	-42

typedef	struct	s_sovle_room
{
	int		id;
	int		x;
	int		y;
	int		*links;
	int		links_num;
}				t_solve_room;

typedef struct	s_solve
{
	t_solve_room	*rooms;
	int				rooms_num;
	int				all_links_num;

}				t_solve;

void	solve(t_map *m);
void	print_data(t_map *m);

#endif
