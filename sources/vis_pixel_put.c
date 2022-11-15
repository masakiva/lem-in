/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:12:57 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/15 15:12:59 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	my_mlx_pixel_put(t_visualizar *v, int x, int y, int color)
{
	char	*dest;

	dest = v->img_addr + (y * v->img_line_lenght + x * (v->img_bit_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	protected_pixel_put(t_visualizar *v, int x, int y, int color)
{
	x += v->world_x;
	y += v->world_y;
	if (x < 0 || y < 0 || v->width <= x || v->height <= y)
		return ;
	my_mlx_pixel_put(v, x, y, color);
}

void	fill_black(t_visualizar *v)
{
	int		x;
	int		y;

	y = 0;
	while (y < v->height)
	{
		x = 0;
		while (x < v->width)
		{
			my_mlx_pixel_put(v, x, y, BLACK);
			x++;
		}
		y++;
	}
}
