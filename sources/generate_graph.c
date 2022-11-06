#include "lem-in.h"
#include "libft.h"
#include "../headers/solve.h"

void	generate_node(t_ek_graph *graph)
{
	int			i;

	i = 0;
	while (i < graph->nodes_size)
	{
		graph->nodes[i].id = i;
		//if ()
		i++;
	}
}

void	generate_graph(t_map *map, t_solve *s, t_ek_graph *graph)
{
	printf("----- generate graph -----\n");
	(void)map;
	//set graph data

	//room => node, link => edge
	//edge * 2(in, out)
	graph->nodes_size = s->rooms_size * 2;
	//node * 2(rev) + edge * 2(both_side) * 2(rev)
	graph->edges_size = s->rooms_size * 2 + s->all_links_size * 2 * 2;

	printf("%d\n", graph->nodes_size);
	printf("%d\n", graph->edges_size);

	//malloc
	graph->nodes = malloc(sizeof(t_ek_edge) * graph->nodes_size);
}
