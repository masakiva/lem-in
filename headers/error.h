/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:25:16 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/07 11:50:42 by mvidal-a         ###   ########.fr       */
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
	BEGIN_WITH_L,
	UNKNOWN_SYNTAX,
	UNKNOWN_SYNTAX_HASH,
	START_END_ROOM_DEF,
};

int		error_exit(enum e_errcode errcode);

#endif // ERROR_H
