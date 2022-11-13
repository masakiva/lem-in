/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:01:00 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 18:29:49 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_bool	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == 1)
		return (SUCCESS);
	return (FAILURE);
}
