/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:10:47 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 18:29:16 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_putendl_fd(const char *s, int fd)
{
	if (ft_putstr_fd(s, fd) == SUCCESS)
		return (ft_putchar_fd('\n', fd));
	return (FAILURE);
}
