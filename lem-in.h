/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/04 12:30:01 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	int		id;
	int		x;
	int		y;
}				t_room;

typedef struct	s_link
{
	int		room1;
	int		room2;
}				t_link;

typedef struct	s_map
{
	t_list	*rooms;
	t_list	*links;
	int		start;
	int		end;
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
	DIGIT,
	HASH,
	DOUBLE_HASH,
	END,
	NB_STATES,
};

typedef struct	s_state_machine
{
	t_map*			map;
	enum e_state	state;
	uint8_t			pad[4];
}				t_state_machine;

typedef char*	(*t_parse)(t_state_machine *, char *);

#endif // LEM_IN_H
