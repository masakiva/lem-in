/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:25:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/07 12:16:08 by mvidal-a         ###   ########.fr       */
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
	BEGIN_WITH_L,
	UNKNOWN_SYNTAX,
	UNKNOWN_SYNTAX_HASH,
	START_END_ROOM_DEF,
	LINK_SAME_ROOMNAMES,
	DUP_ROOMNAME,
	DUP_ROOMCOORD,
	DUP_LINK,
	UNKNOWN_LINK,
};

int		error_exit(enum e_errcode errcode);

#endif // ERROR_H
