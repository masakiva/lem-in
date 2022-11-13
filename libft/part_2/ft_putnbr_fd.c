/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:12:53 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 18:31:32 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_bool	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	else if (n < 0)
	{
		if (ft_putchar_fd('-', fd) != SUCCESS)
			return (FAILURE);
		n *= -1;
	}
	if (n > 9)
	{
		if (ft_putnbr_fd(n / 10, fd) != SUCCESS)
			return (FAILURE);
	}
	digit = n % 10 + '0';
	return (ft_putchar_fd(digit, fd));
}
