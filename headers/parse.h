/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 20:25:39 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "error.h"
# include "ft_queue.h"

# define ARG_OPTIONS	"hv"
# define HELP_OPTION	0x01
# define VISUAL_OPTION	0x02
# define LONG_HELP_OPTION	"help"
# define LONG_VISUAL_OPTION	"visual"

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
	t_queue	line_queue;
	t_list*	rooms;
	t_list*	links;
	char*	start;
	char*	end;
	int		nb_ants;
	t_bool	start_flag;
	t_bool	end_flag;
	t_bool	visual;
	t_byte	pad[1];
}				t_map;

enum	e_state
{
	CHARACTER,
	NB_ANTS,
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


t_byte	retrieve_options(int argc, char **argv, char *op_chars);

int		parse_line(t_map* map);

void	check_input(t_map* map);

// state machine states
char*	character(t_state_machine* machine, char* line);
char*	nb_ants(t_state_machine* machine, char* line);
char*	roomname(t_state_machine* machine, char* line);
char*	hash(t_state_machine* machine, char* line);
char*	double_hash(t_state_machine* machine, char* line);
char*	start_end_line(t_state_machine* machine, char* line);

// utils
int		ft_str_isnumber(char* str);
int		ispositiveint(char* line);
int		isroom(char* line);
int		islink(char* line);
void	parse_room(char* line, t_map* map);
void	parse_link(char* line, t_map* map);

#endif // PARSE_H
