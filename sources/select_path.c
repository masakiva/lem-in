#include "libft.h"
#include "parse.h"
#include "../headers/solve.h"

void	check_all_path(t_solve *s, t_ek_graph *graph)
{
	t_path_manager	*m;
	t_list			*front;
	t_path_set		*path_set;
	t_path			**paths;

	m = &graph->path_manager;

	front = m->path_sets_list;

	printf("--- check all path ---\n");
	while (front)
	{
		path_set = (t_path_set *)front->content;
		paths = path_set->paths;
		printf("\n[[ path num %d ]]\n", path_set->paths_size);
		while (*paths)
		{
			printf("- path size %d -\n", (*paths)->root_size);
			display_struct_path(*paths, s);
			paths++;
		}

		front = front->next;
	}
	(void)s;
}

void	select_path(t_map *map, t_solve *s, t_ek_graph *graph)
{
	(void)map;
	check_all_path(s, graph);
}
