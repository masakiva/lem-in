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

void drawCircle(int radius, int x1, int y1, t_visualizar *v, int color)
{
	int x, y;
	int dx, dy;

	for(y = 0 + y1 - radius; y < y1 + radius; y++)
	{
		for(x = 0 + x1 - radius; x < x1 + radius; x++)
		{
			dx = (int)x - (int)x1;
			dy = (int)y - (int)y1;

			/* 円を描画 */
			if((dx * dx) + (dy * dy) <= radius * radius)
			{
				protected_pixel_put(v, x, y, color);
			}
		}
	}
}

void drawLineTwoPixels(int xs, int ys, int xe, int ye, t_visualizar *v)
{
	int x, y;
	int dx, dy;
	double rad;
	int length;
	int l;

	dx = xe - xs;
	dy = ye - ys;

	length = sqrt(dx * dx + dy * dy);

	rad = atan2(dy, dx);

 	for(l = 0; l < length; l++)
	{
    	x = xs + l * cos(rad);
    	y = ys + l * sin(rad);
		protected_pixel_put(v, x, y, LIME);
    }
}

void	put_nodes(t_visualizar *v)
{
	int		i = 0;

	while (i < v->nodes_size)
	{
		//protected_pixel_put(v, v->nodes[i].v_x * v->display_ratio,
		//			v->nodes[i].v_y * v->display_ratio, LIME);
		drawCircle(30, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, LIME);
		drawCircle(28, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, BLACK);
		i++;
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
		drawLineTwoPixels(x, y, node->x * v->display_ratio, node->y * v->display_ratio, v);
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

int	ft_key_reflect(t_visualizar *v)
{
	fill_black(v);
	put_node_link(v);
	put_nodes(v);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);
	return (0);
}

int		visualizar_exit(t_visualizar *v)
{
	printf("pressed [x]\n");
	exit(0);
	(void)v;
}

void	update_display_ratio(int isUp, t_visualizar *v)
{
	v->display_ratio += isUp;
	if (v->display_ratio < 1)
		v->display_ratio = 1;
}

void	update_world_cordinate(t_visualizar *v, int key)
{
	int x = 0;
	int y = 0;
	int move_size = 20;

	if (key == KEY_W)
		y = -move_size;
	if (key == KEY_S)
		y = move_size;
	if (key == KEY_A)
		x = -move_size;
	if (key == KEY_D)
		x = move_size;
	v->world_x += x;
	v->world_y += y;
}

int		ft_key_pressed(int key, t_visualizar *v)
{
	printf("pressed [%d]\n", key);
	if (key == KEY_ESC)
		visualizar_exit(v);
	if (key == KEY_UP)
		update_display_ratio(10, v);
	if (key == KEY_DOWN)
		update_display_ratio(-10, v);
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
		update_world_cordinate(v, key);


	ft_key_reflect(v);

	return 0;
}


void	v_loop(t_visualizar *v)
{
	mlx_hook(v->win_ptr, 2, 1L << 0, ft_key_pressed, v);
	mlx_hook(v->win_ptr, EVENT_EXIT, 1L << 0, visualizar_exit, v);
	//mlx_loop_hook(d->mlx_ptr, ft_key_reflect, d);
	mlx_loop(v->mlx_ptr);
}

void	visualize_lem_in_init(t_visualizar *v, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int		i;

	v->map = map;
	v->s = s;
	v->graph = graph;

	v->nodes = malloc(sizeof(t_v_node) * s->rooms_size);
	v->nodes_size = s->rooms_size;
	i = 0;
	while (i < s->rooms_size)
	{
		v->nodes[i].id = i;
		v->nodes[i].v_x = v->s->rooms[i].x;
		v->nodes[i].v_y = v->s->rooms[i].y;
		i++;
	}
	v->display_ratio = 1;
	v->world_x = 100;
	v->world_y = 100;
}

void	visualize_mlx_init(t_visualizar *v)
{
	v->mlx_ptr = mlx_init();
	v->width = WINDOW_WIDHT;
	v->height = WINDOW_HEIGHT;
	v->win_ptr = mlx_new_window(v->mlx_ptr, v->width, v->height, "lem_in");
	
	int		tmp;

	v->img_ptr = mlx_new_image(v->mlx_ptr, v->width, v->height);
	v->img_addr = mlx_get_data_addr(v->img_ptr, &v->img_bit_per_pixel,
			&v->img_line_lenght, &tmp);
}

void	lem_in_visualizar(t_map *map, t_solve *s, t_ek_graph *graph)
{
	printf("--- visualize ---\n");

	t_visualizar	tmp_v;
	t_visualizar	*v = &tmp_v;

	visualize_mlx_init(v);
	visualize_lem_in_init(v, map, s, graph);

	v_loop(v);
}

