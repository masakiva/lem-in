/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 18:26:07 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"

typedef t_byte	t_bool;

typedef struct	s_room
{
	char*	name;
	int		x;
	int		y;
}				t_room;

typedef struct	s_link
{
	char*	room1;
	char*	room2;
}				t_link;

typedef struct	s_map
{
	t_list*	rooms;
	t_list*	links;
	char*	start;
	char*	end;
	t_bool	start_flag;
	t_bool	end_flag;
	t_byte	pad[6];
}				t_map;

enum	e_err_code
{
	GNL_ERR,
	INPUT_ERR,
	MALLOC_ERR,
};


enum	e_state
{
	CHARACTER,
	ROOMNAME,
	HASH,
	DOUBLE_HASH,
	START_END_LINE,
	END,
	NB_STATES,
};

typedef struct	s_state_machine
{
	t_map*			map;
	enum e_state	state;
	t_byte			pad[4];
}				t_state_machine;

typedef char*	(*t_parse)(t_state_machine *, char *);

int		parse_line(t_map* map);

#endif // PARSE_H
