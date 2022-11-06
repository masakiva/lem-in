/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 20:40:38 by mvidal-a         ###   ########.fr       */
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


// state machine states
char*	character(t_state_machine* machine, char* line);
char*	roomname(t_state_machine* machine, char* line);
char*	hash(t_state_machine* machine, char* line);
char*	double_hash(t_state_machine* machine, char* line);
char*	start_end_line(t_state_machine* machine, char* line);

// utils
int		isroom(char* line);
int		islink(char* line);
void	parse_room(char* line, t_map* map);
void	parse_link(char* line, t_map* map);
t_bool	find_dup_roomname(t_list* rooms, char* name_to_compare);
t_bool	find_dup_roomcoord(t_list* rooms, t_room* room_to_compare);
t_bool	find_dup_link(t_list* links, t_link* link_to_compare);

#endif // PARSE_H
