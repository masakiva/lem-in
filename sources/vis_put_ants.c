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

	if (is_end)
	{
		drawCircle(9, 
			x * v->display_ratio,
			y * v->display_ratio,
			v, WHITE);
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

	x = x + length * v->move_frame / 1000 * cos(rad);
	y = y + length * v->move_frame / 1000 * sin(rad);
	
	drawCircle(9, x, y, 
			v, RED);



//	drawCircle(10, 
//			x * v->display_ratio,
//			y * v->display_ratio,
//			v, LIME);
}

void	draw_ant_name(t_visualizar *v, t_ant *ant, int pos_index)
{
	int		node_id = ant->path->root[pos_index];

	int		x = v->s->rooms[node_id].x;
	int		y = v->s->rooms[node_id].y;

	char	*ant_name;
	char	*tmp;

	tmp = ft_itoa(ant->id);
	ant_name = ft_strjoin(" ant_id: ", tmp);

	mlx_string_put(v->mlx_ptr, v->win_ptr,
			x * v->display_ratio + v->world_x + 10,
			y * v->display_ratio + v->world_y,
			RED,
			ant_name);
	free(ant_name);
	free(tmp);
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

	m = &v->s->ant_manager;
	while (i < v->s->ant_size)
	{
		is_end = 0;
		ant = &m->ants[i];
		pos_index = v->turn - ant->start_turn;
		//min
		if (pos_index < 0)
			pos_index = 0;
		//max
		if (ant->path->root_size <= pos_index + 1)
		{
			pos_index = ant->path->root_size - 1;
			is_end = 1;
		}

		draw_ants(v, ant, pos_index, is_end);

		//printf("id: %d pos: %d limit %d ", ant->id, pos_index, ant->path->root_size);
		//printf("room_id: %d room: %s\n", ant->path->root[pos_index], v->s->rooms[ant->path->root[pos_index]].name_ptr);
		i++;
	}
	(void)v;
}
