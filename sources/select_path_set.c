#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

void	show_path(t_path *path, t_map *map, t_solve *s, t_ek_graph *graph)
{
	int			i;

	i = 0;
	printf("<start>\n");
	while (i < path->root_size)
	{
		printf("root: [%s]\n", s->rooms[path->root[i]].name_ptr);
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
		printf("path num => [%d]\n", num++);
		path_set = (t_path_set *)node->content;
		show_path_set(path_set, map, s, graph);
		node = node->next;
	}
}

void	select_path_set(t_map *map, t_solve *s, t_ek_graph *graph)
{
	show_all_path(map, s, graph);
}
