/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:06:07 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 18:23:59 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_bool		ft_putstr_fd(const char *s, int fd)
{
	size_t	len;
	ssize_t	ret;

	len = ft_strlen(s);
	ret = write(fd, s, len);
	if (ret != (ssize_t)len)
		return (FAILURE);
	return (SUCCESS);
}
