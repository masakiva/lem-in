/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:17:33 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/08 14:35:40 by mvidal-a         ###   ########.fr       */
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
		"Number of ants must be a positive integer",
		"Number of ants cannot be defined twice",
		"Number of ants needed before room definitions",
		"Room name cannot begin with the L character",
		"Duplicate room name",
		"Duplicate room coordinates",
		"##start or ##end must be followed by a room definition",
		"Duplicate ##start label",
		"Duplicate ##end label",
		"##start and ##end rooms must be defined",
		"Room definitions needed before link definitions",
		"Link with unknown room name",
		"Link with same room names",
		"Duplicate link",
		"Unknown syntax",
	};

	ft_putstr_fd("[lem-in] error: ", STDERR_FILENO);
	ft_putstr_fd(err_msg[errcode], STDERR_FILENO);
	if (errcode < _ERRNO_END_)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);

	exit(EXIT_FAILURE);
}
