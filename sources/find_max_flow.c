#include "libft.h"
#include "parse.h"
#include "../headers/solve.h"

void	max_flow_init(t_ek_graph *graph)
{
	graph->used = malloc(sizeof(int) * graph->nodes_size);
}

void	used_set_zero(t_ek_graph *graph)
{
	int		i;

	i = 0;
	while (i < graph->nodes_size)
		graph->used[i++] = 0;
}

void	find_max_flow(t_map *map, t_solve *s, t_ek_graph *graph)
{
	(void)map;
	(void)s;
	max_flow_init(graph);
	used_set_zero(graph);
	while (1)
	{
		break;
	}
}
