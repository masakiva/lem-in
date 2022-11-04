/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:54 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/04 11:28:41 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

enum	e_err_code
{
	GNL_ERR,
};


# define BUF_SIZE	4096

enum	e_state
{
	SPACE,
	LETTER,
	HASH,
	END,
	NB_STATES
};

typedef struct	s_state_machine
{
	char			buf[BUF_SIZE];
	size_t			len;
	enum e_state	state;
	uint8_t			pad[4];
}				t_state_machine;

typedef void	(*t_parse)(t_state_machine *, char *);

#endif // LEM_IN_H
