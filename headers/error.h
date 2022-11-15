/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:25:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/15 16:32:52 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"

# define HELP_MSG	"[lem-in] usage example:\n\n"\
	"./lem-in [--visual] < maps/subject/subject3.map\n\n"\
	"provide data describing the ant "\
	"farm in standard input in the following format:\n"\
	"\tnumber_of_ants\n"\
	"\tthe_rooms\n"\
	"\tthe_links\n"\
	"for example:\n"\
	"\t3\n"\
	"\t##start\n"\
	"\t0 1 0\n"\
	"\t1 5 0\n"\
	"\t##end\n"\
	"\t2 9 0\n"\
	"\t0-1\n"\
	"\t1-2\n"

enum		e_errcode
{
	MALLOC_ERR,
	WRITE_ERR,
	GNL_ERR,
	_ERRNO_END_,
	NB_ANTS_MANDATORY,
	POSITIVE_NB_ANTS,
	DUP_NB_ANTS,
	BEGIN_WITH_L,
	COORD_INT_OVERFLOW,
	DUP_ROOMNAME,
	DUP_ROOMCOORD,
	START_END_ROOM_DEF,
	DUP_START,
	DUP_END,
	START_END_MANDATORY,
	ROOMS_MANDATORY,
	LINK_UNKNOWN_ROOMNAME,
	LINK_SAME_ROOMNAMES,
	ROOM_AFTER_LINK,
	UNKNOWN_SYNTAX,
	INPUT_MISSING,
	ROOMS_LINKS_MISSING,
	LINKS_MISSING,
	UNSOLVABLE,
};

int		error_exit(enum e_errcode errcode);

#endif // ERROR_H
