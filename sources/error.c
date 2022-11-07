/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:17:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/07 12:18:24 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int		error_exit(enum e_errcode errcode)
{
	const char		*err_msg[] = {
		"Memory allocation failure",
		"Cannot write on standard output",
		"Cannot read standard input (GNL error)",
		"--- separator ---",
		"Room name cannot begin with the L character",
		"Unknown syntax",
		"Unknown syntax after ## signs",
		"##start or ##end must be followed by a room definition",
		"Link with same room names",
		"Duplicate room name",
		"Duplicate room coordinates",
		"Duplicate link",
		"Link with unknown room name",
	};

	ft_putstr_fd("lem-in error: ", STDERR_FILENO);
	ft_putstr_fd(err_msg[errcode], STDERR_FILENO);
	if (errcode < _ERRNO_END_)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);

	exit(EXIT_FAILURE);
}
