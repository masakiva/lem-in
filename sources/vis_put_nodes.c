/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:11:13 by tkodai            #+#    #+#             */
/*   Updated: 2022/11/29 15:01:00 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	put_nodes(t_visualizar *v)
{
	int		i = 0;

	while (i < v->nodes_size)
	{
		draw_circle(30, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, LIME);
		draw_circle(28, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, BLACK);
		i++;
	}
}

void	put_nodes_name(t_visualizar *v)
{
	int		i = 0;

	while (i < v->nodes_size)
	{
		mlx_string_put(v->mlx_ptr, v->win_ptr,
				v->nodes[i].v_x * v->display_ratio + v->world_x,
				v->nodes[i].v_y * v->display_ratio + v->world_y,
				LIME,
		       	v->s->rooms[i].name_ptr);
		i++;
	}
}

void	put_line_variable_width(int x1, int y1, int x2, int y2,
							t_visualizar *v, int color, int width)
{
	int		x = 0;
	int		y = 0;

	while (y < width)
	{
		x = 0;
		while (x < width)
		{
			draw_line_two_pixels2(x1 + x, y1 + y, x2 + x, y2 + y, v, color, x1, y1);
			x++;
		}
		y++;
	}
}

void	put_node_link2(t_visualizar *v, t_solve_room *node, int id)
{
	int		i = 0;
	int		x;
	int		y;
	int		opponent_id;

	id = 0;
	while (i < node->links_size)
	{
		opponent_id = node->links[i];	
		x = v->s->rooms[opponent_id].x * v->display_ratio;
		y = v->s->rooms[opponent_id].y * v->display_ratio;
		draw_line_two_pixels(x, y, node->x * v->display_ratio, node->y * v->display_ratio, v, LIME);
		//put_line_variable_width(x, y, node->x * v->display_ratio,
		//		node->y * v->display_ratio, v, LIME, 1);

		i++;
	}
}

void	put_node_link(t_visualizar *v)
{
	int				i = 0;
	t_solve_room	*node;

	while (i < v->nodes_size)
	{
		node = &v->s->rooms[i];
		put_node_link2(v, node, i);
		i++;
	}
}



void	put_use_link2(t_visualizar *v, t_path *path)
{
	int		old;
	int		id;
	int		i = 1;
	int		x;
	int		y;

	old = path->root[0];
	while (i < path->root_size)
	{
		id = path->root[i];
		x = v->s->rooms[old].x * v->display_ratio;
		y = v->s->rooms[old].y * v->display_ratio;
		put_line_variable_width(
				v->s->rooms[id].x * v->display_ratio,
				v->s->rooms[id].y * v->display_ratio,
				x, y, v, LIME, 5);	
		old = path->root[i];
		i++;
	}
}

void	put_use_link(t_visualizar *v)
{
	t_path_set	*path_set;
	t_path		*path;
	int			i = 0;

	path_set = v->graph->path_manager.current_path_set;
	while (i < path_set->paths_size)
	{
		path = path_set->paths[i];
		put_use_link2(v, path);
		i++;
	}
}
#endif // BONUS
