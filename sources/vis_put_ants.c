#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	draw_ants(t_visualizar *v, t_ant *ant, int pos_index)
{
	int		node_id = ant->path->root[pos_index];

	int		x = v->s->rooms[node_id].x;
	int		y = v->s->rooms[node_id].y;

	char	*ant_name;

	ant_name = ft_itoa(ant->id);
	//ant_name = ft_strjoin("ant_id: ", ant_name);

	mlx_string_put(v->mlx_ptr, v->win_ptr,
			x * v->display_ratio + v->world_x,
			y * v->display_ratio + v->world_y,
			RED,
			ant_name);
	drawCircle(10, 
			x * v->display_ratio,
			y * v->display_ratio,
			v, LIME);
	drawCircle(9, 
			x * v->display_ratio,
			y * v->display_ratio,
			v, THIN_LIME);
	//printf("x %d y %d\n", x, y);

	free(ant_name);
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
		if (ant->path->root_size < pos_index + 1)
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

	m = &v->s->ant_manager;
	while (i < v->s->ant_size)
	{
		ant = &m->ants[i];
		pos_index = v->turn - ant->start_turn;
		//min
		if (pos_index < 0)
			pos_index = 0;
		//max
		if (ant->path->root_size < pos_index + 1)
			pos_index = ant->path->root_size - 1;

		draw_ants(v, ant, pos_index);

		//printf("id: %d pos: %d limit %d ", ant->id, pos_index, ant->path->root_size);
		//printf("room_id: %d room: %s\n", ant->path->root[pos_index], v->s->rooms[ant->path->root[pos_index]].name_ptr);
		i++;
	}
	(void)v;
}
