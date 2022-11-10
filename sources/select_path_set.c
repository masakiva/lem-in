#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

void	show_path(t_path *path, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int			i;

	i = 0;
	printf("<start> (%d) use: %d\n", path->root_size, path->use_num);
	while (i < path->root_size)
	{
		printf(" root: [%s]\n", s->rooms[path->root[i]].name_ptr);
		i++;
	}
	printf("<end>\n");
	(void)s;
	(void)map;
	(void)graph;
}

void	show_path_set(t_path_set *path_set, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int			i;
	t_path		*path;

	i = 0;
	while (i < path_set->paths_size)
	{
		path = path_set->paths[i];
		show_path(path, map, s, graph);
		i++;
	}
	(void)s;
	(void)map;
	(void)graph;
}

void	show_all_path(t_map *map, t_solve *s, t_ek_graph *graph)
{
	t_path_manager	*m;
	t_list			*node;
	t_path_set		*path_set;
	int				num;

	m = &(graph->path_manager);
	node = m->path_set_list;

	num = 1;
	while (node)
	{
		printf("\npath num => [%d]\n", num++);
		path_set = (t_path_set *)node->content;
		show_path_set(path_set, map, s, graph);
		node = node->next;
	}
}

int		ft_max(int x1, int x2)
{
	if (x1 < x2)
		return x2;
	return x1;
}

int		count_flow_path(t_path *path, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int				ant_num = 0;
	t_path_manager	*m;

	m = &(graph->path_manager);
	printf(" root size [%d] ant: [%d]\n",
			path->root_size, ft_max(0, m->turn - path->root_size + 2));
	ant_num = ft_max(0, m->turn - path->root_size + 2);
	if (ant_num > 0)
		path->use_num++;
	return ant_num;
	(void)s;
	(void)map;
	(void)graph;


}

void	check_flow_path(t_path_set *path_set, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int			i;
	t_path		*path;
	int			ant_num = 0;

	i = 0;
	while (i < path_set->paths_size)
	{
		path = path_set->paths[i];
		ant_num += count_flow_path(path, map, s, graph);
		i++;
	}
	if (ant_num >= s->ant_size)
	{
		graph->path_manager.current_path_set = path_set;
	}
	(void)s;
	(void)map;
	(void)graph;
	
}

void	check_all_roots(t_map *map, t_solve *s, t_ek_graph *graph)
{
	t_path_manager	*m;
	t_list			*node;
	t_path_set		*path_set;

	m = &(graph->path_manager);
	node = m->path_set_list;
	m->current_path = NULL;
	m->current_path_set = NULL;
	m->turn = 0;

	while (m->current_path_set == NULL)
	{
		m->turn++;
		printf("\n======== TURN [%d] ========\n", m->turn);
		node = m->path_set_list;
		while (node)
		{
			printf("-------- PATH SET --------\n");	
			path_set = (t_path_set *)node->content;
			check_flow_path(path_set, map, s, graph);
			node = node->next;
		}
	}
	(void)s;
	(void)map;
	(void)graph;
}


void	select_path_set(t_map *map, t_solve *s, t_ek_graph *graph)
{
	show_all_path(map, s, graph);
	check_all_roots(map, s, graph);

	printf("\n\n==> best path set: ant size: [%d] turn: [%d]\n",
			s->ant_size, graph->path_manager.turn);
	show_path_set(graph->path_manager.current_path_set, map, s, graph);
}
