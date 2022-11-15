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
		drawCircle(30, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, LIME);
		drawCircle(28, v->nodes[i].v_x * v->display_ratio,
				v->nodes[i].v_y * v->display_ratio, v, BLACK);
		i++;
	}
}

unsigned long long int get_cycle() {
  unsigned int low, high;
  __asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
  return ((unsigned long long int) low) | ((unsigned long long int) high << 32);
}

double get_time(unsigned long long int begin_cycle) {
  return (double) (get_cycle() - begin_cycle) / CYCLE_PER_SEC;
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
			drawLineTwoPixels2(x1 + x, y1 + y, x2 + x, y2 + y, v, color, x1, y1);
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
		drawLineTwoPixels(x, y, node->x * v->display_ratio, node->y * v->display_ratio, v, LIME);
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

int	ft_key_reflect(t_visualizar *v)
{
	mlx_do_sync(v->mlx_ptr);
	
	//frame
	v->move_frame = (int)(get_time(v->first_time) / FLOW_SPEED * FRAME_RATIO) % FRAME_RATIO;
	if (v->is_flow == 1)
		v->turn = (int)get_time(v->first_time) / FLOW_SPEED % (v->graph->path_manager.turn + 2);

	fill_black(v);
	put_node_link(v);
	put_use_link(v);
	put_nodes(v);
	vis_put_ants(v);

	//printf("wx: %d wy: %d mx %d my %d dratio %d\n", v->world_x, v->world_y, v->mouse_x, v->mouse_y, v->display_ratio);
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);

	//string puts
	//put_nodes_name(v);
	put_info(v);
	set_coordinate(v, v->mouse_x, v->mouse_y);
	put_buffer(v, v->mouse_x, v->mouse_y);
	put_buffer(v, 30, 30);

	//tmp TODO delete 
	vis_put_ants_name(v);
	put_nodes_name(v);

	if (VISUAL_PRINTF)
		printf("turn [%d]\n", v->turn);
	if (VISUAL_PRINTF)
		printf("time [%f]\n", get_time(v->first_time));
	return (0);
}

int		visualizar_exit(t_visualizar *v)
{
	if (VISUAL_PRINTF)
		printf("pressed [x]\n");
	exit(0);
	(void)v;
}

void	update_display_ratio(int isUp, t_visualizar *v)
{
	int		ratio = v->display_ratio;
	
	int		old_mouse_x = v->mouse_x - v->world_x;;
	int		old_mouse_y = v->mouse_y - v->world_y;

	v->display_ratio += isUp;

	int		move_mouse_x = old_mouse_x * v->display_ratio / ratio;
	int		moved_x = move_mouse_x - old_mouse_x;

	int		move_mouse_y = old_mouse_y * v->display_ratio / ratio;
	int		moved_y = move_mouse_y - old_mouse_y;

	if (ratio < 0)
		ratio = 1;
	if (v->display_ratio < 1)
		v->display_ratio = 1;
	else
	{
		v->world_x -= moved_x;
		v->world_y -= moved_y;
	}
}

void	update_world_cordinate(t_visualizar *v, int key)
{
	int x = 0;
	int y = 0;
	int move_size = 10;

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

void	update_turn(t_visualizar *v, int step)
{
	v->turn += step;
	if (v->turn < 0)
		v->turn = 0;
	if (v->turn > v->graph->path_manager.turn)
		v->turn = v->graph->path_manager.turn;
}

void	reset_all(t_visualizar *v)
{
	v->first_time = get_cycle();
	v->turn = 0;
}

void	position_reset(t_visualizar *v)
{
	v->display_ratio = 100;
	v->world_x = 200;
	v->world_y = 200;
}

void	flow_ants_start(t_visualizar *v)
{
	reset_all(v);
	if (v->is_flow == 1)
		v->is_flow = 0;
	else
		v->is_flow = 1;
}

int		ft_key_pressed(int key, t_visualizar *v)
{
	if (VISUAL_PRINTF)
		printf("pressed [%d]\n", key);
	if (key == KEY_ESC)
		visualizar_exit(v);
	if (key == KEY_UP)
		update_display_ratio(1, v);
	if (key == KEY_DOWN)
		update_display_ratio(-1, v);
	if (key == KEY_W || key == KEY_A || key == KEY_D || key == KEY_S)
		update_world_cordinate(v, key);
	if (key == KEY_N)
		update_turn(v, 1);
	if (key == KEY_P)
		update_turn(v, -1);
	if (key == KEY_B)
		reset_all(v);
	if (key == KEY_0)
		position_reset(v);
	if (key == KEY_F)
		flow_ants_start(v);
	if (key == KEY_I)
		ant_num_change(v, 1);
	if (key == KEY_U)
		ant_num_change(v, -1);
	if (key == KEY_R)
		ant_num_reset(v);

	ft_key_reflect(v);

	return 0;
}

int		ft_mouse_pressed(int button, int x,int y, t_visualizar *v)
{
	if (VISUAL_PRINTF)
		printf("button press: %d x: %d y: %d\n", button, x, y);
	if (button == 4) //scroll up
		update_display_ratio(ZOOM_STEP, v);
	if (button == 5) //scroll down
		update_display_ratio(-ZOOM_STEP, v);
	if (button == 1)
		v->mouse_button1_pressed = 1;
	ft_key_reflect(v);
	return 0;
}

int		ft_mouse_released(int button, int x,int y, t_visualizar *v)
{
	if (VISUAL_PRINTF)
		printf("button released: %d x: %d y: %d\n", button, x, y);
	if (button == 1)
		v->mouse_button1_pressed = 0;
	ft_key_reflect(v);
	return 0;
}


int		ft_mouse_moved(int x,int y, t_visualizar *v)
{
	if (VISUAL_PRINTF)
		printf("move x: %d y: %d\n", x, y);
	
	if (v->mouse_button1_pressed == 1)
	{
		v->world_x += x - v->mouse_x;
		v->world_y += y - v->mouse_y;
	}

	v->mouse_x = x;
	v->mouse_y = y;
	ft_key_reflect(v);
	return 0;
}

void	v_loop(t_visualizar *v)
{
	ft_key_reflect(v);
	mlx_hook(v->win_ptr, 2, 1L << 0, ft_key_pressed, v);
	mlx_hook(v->win_ptr, EVENT_EXIT, 1L << 0, visualizar_exit, v);
	mlx_hook(v->win_ptr, 4, 1L << 0, ft_mouse_pressed, v);
	mlx_hook(v->win_ptr, 5, 1L << 0, ft_mouse_released, v);
	mlx_hook(v->win_ptr, 6, 1L << 0, ft_mouse_moved, v);
	mlx_loop_hook(v->mlx_ptr, ft_key_reflect, v);
	mlx_loop(v->mlx_ptr);
}

void	visualize_lem_in_init(t_visualizar *v, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int		i;

	v->map = map;
	v->s = s;
	v->graph = graph;

	v->nodes = malloc(sizeof(t_v_node) * s->rooms_size);
	if (v->nodes == NULL)
		error_exit(MALLOC_ERR);
	v->nodes_size = s->rooms_size;
	i = 0;
	while (i < s->rooms_size)
	{
		v->nodes[i].id = i;
		v->nodes[i].v_x = v->s->rooms[i].x;
		v->nodes[i].v_y = v->s->rooms[i].y;
		i++;
	}
	v->display_ratio = 100;
	v->world_x = 200;
	v->world_y = 200;
	v->mouse_x = WINDOW_WIDHT / 2;
	v->mouse_y = WINDOW_HEIGHT / 2;
	v->mouse_button1_pressed = 0;

	v->first_time = get_cycle();
	v->move_frame = 0;
	v->turn = 0;
	v->is_flow = 0;
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
	//printf("--- visualize ---\n");

	t_visualizar	tmp_v;
	t_visualizar	*v = &tmp_v;

	visualize_mlx_init(v);
	visualize_lem_in_init(v, map, s, graph);

	v_loop(v);
}

