/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_put_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:13:04 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/15 15:13:08 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	draw_ants(t_visualizar *v, t_ant *ant, int pos_index, int is_end)
{
	int		node_id = ant->path->root[pos_index];
	int		x = v->s->rooms[node_id].x;
	int		y = v->s->rooms[node_id].y;

	if (is_end || v->is_flow == 0)
	{
		drawCircle(8, 
			x * v->display_ratio,
			y * v->display_ratio,
			v, LIME);
		drawCircle(7, 
			x * v->display_ratio,
			y * v->display_ratio,
			v, WHITE);
		ant->visualize_x = x * v->display_ratio;
		ant->visualize_y = y * v->display_ratio;
		return ;
	}
	int		next_id = ant->path->root[pos_index + 1];
	int		nx = v->s->rooms[next_id].x * v->display_ratio;
	int		ny = v->s->rooms[next_id].y * v->display_ratio;
			x = x * v->display_ratio;
			y = y * v->display_ratio;
	int		dx = nx - x;
	int		dy = ny - y;
	double	rad;
	int		length = sqrt(dx * dx + dy * dy);

	rad = atan2(dy, dx);

	x = x + length * v->move_frame / FRAME_RATIO * cos(rad);
	y = y + length * v->move_frame / FRAME_RATIO * sin(rad);
	
	drawCircle(8, x, y, 
			v, LIME);
	drawCircle(7, x, y, 
			v, WHITE);

	ant->visualize_x = x;
	ant->visualize_y = y;

}

void	draw_ant_name(t_visualizar *v, t_ant *ant, int pos_index)
{
	char	*ant_name;
	char	*tmp;

	tmp = ft_itoa(ant->id);
	ant_name = ft_strjoin(" id: ", tmp);

	mlx_string_put(v->mlx_ptr, v->win_ptr,
			ant->visualize_x + v->world_x + 10,
			ant->visualize_y + v->world_y,
			WHITE,
			ant_name);
	free(ant_name);
	free(tmp);
	pos_index = 0;
}


void	vis_put_ants_name(t_visualizar *v)
{
	t_ant_manager	*m;
	t_ant			*ant;
	int				i = 0;
	int				pos_index = 0;

	m = &v->s->ant_manager;
	while (i < v->s->ant_size)
	{
		ant = &m->ants[i];
		pos_index = v->turn - ant->start_turn;
		//min
		if (pos_index < 0)
			pos_index = 0;
		//max
		if (ant->path->root_size <= pos_index + 1)
			pos_index = ant->path->root_size - 1;

		draw_ant_name(v, ant, pos_index);
		//printf("id: %d pos: %d limit %d ", ant->id, pos_index, ant->path->root_size);
		//printf("room_id: %d room: %s\n", ant->path->root[pos_index], v->s->rooms[ant->path->root[pos_index]].name_ptr);
		i++;
	}


}

void	vis_put_ants(t_visualizar *v)
{
	t_ant_manager	*m;
	t_ant			*ant;
	int				i = 0;
	int				pos_index = 0;
	int				is_end;
	
	v->start_ants = 0;
	v->end_ants = 0;

	m = &v->s->ant_manager;
	while (i < v->s->ant_size)
	{
		is_end = 0;
		ant = &m->ants[i];
		pos_index = v->turn - ant->start_turn;
		//min
		if (pos_index < 0)
		{
			pos_index = 0;
			is_end = 1;
			v->start_ants++;
		}
		else if (pos_index == 0)
			v->start_ants++;
		//max
		if (ant->path->root_size <= pos_index + 1)
		{
			pos_index = ant->path->root_size - 1;
			is_end = 1;
			v->end_ants++;
		}

		draw_ants(v, ant, pos_index, is_end);

		//printf("id: %d pos: %d limit %d ", ant->id, pos_index, ant->path->root_size);
		//printf("room_id: %d room: %s\n", ant->path->root[pos_index], v->s->rooms[ant->path->root[pos_index]].name_ptr);
		i++;
	}
	(void)v;
}
