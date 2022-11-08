/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:25:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/08 09:33:14 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include "libft.h"

enum		e_errcode
{
	MALLOC_ERR,
	WRITE_ERR,
	GNL_ERR,
	_ERRNO_END_,
	DUP_NB_ANTS,
	NB_ANTS_MANDATORY,
	UNKNOWN_SYNTAX_HASH,
	START_END_ROOM_DEF,
	BEGIN_WITH_L,
	DUP_ROOMNAME,
	DUP_ROOMCOORD,
	LINK_UNKNOWN_ROOMNAME,
	LINK_SAME_ROOMNAMES,
	DUP_LINK,
	UNKNOWN_SYNTAX,
};

int		error_exit(enum e_errcode errcode);

#endif // ERROR_H
