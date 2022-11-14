#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"


void	visualize_lem_in_init2(t_visualizar *v, t_map *map, t_solve *s, t_ek_graph *graph)
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

	v->first_time = get_cycle();
	v->move_frame = 0;
	v->turn = 0;
	//v->is_flow = 0;
}

void	reset_simulation(t_visualizar *v)
{
	free(v->nodes);
	v->nodes = NULL;
	free(v->s->ant_manager.ants);
	v->s->ant_manager.ants = NULL;

	t_list *node;
	t_list *del;

	node = v->s->ant_manager.path_list;
	while (node)
	{
		del = node;
		node = node->next;
		free(del);
	}
	v->s->ant_manager.path_list = NULL;
	//path set init

	t_path_set	*path_set;
	t_path		*path;
	node = v->graph->path_manager.path_set_list;
	while (node)
	{
		path_set = (t_path_set *)node->content;
		int i = 0;

		while (i < path_set->paths_size)
		{
			path = path_set->paths[i];
			path->use_num = 0;
			i++;
		}
		node = node->next;
	}
	//reset


	select_path_set(v->map, v->s, v->graph);
	flow_ants_from_visualizar(v->map, v->s, v->graph);
	visualize_lem_in_init2(v, v->map, v->s, v->graph);
}

void	ant_num_change(t_visualizar *v, int num)
{
	if (v->s->ant_size + num <= 0)
		return ;

	v->s->ant_size = v->s->ant_size += num;
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("number_of_ants => ", 1);
	ft_putnbr_fd(v->s->ant_size, 1);
	ft_putstr_fd("\n\n", 1);
	reset_simulation(v);
}
