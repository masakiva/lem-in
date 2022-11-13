#include "libft.h"
#include "parse.h"
#include "../headers/solve.h"

#if 0
void	show_graph(t_ek_graph *graph)
{
	int i = 0;

	return ;
	while (i < graph->nodes_size)
	{
		printf("node: real id: [%d] id: [%d]", graph->nodes[i].id / 2, graph->nodes[i].id);
		if (i % 2 == 0)
			printf("[in ]");
		else
			printf("[out]");

		printf(" edge: ");
		for (int j = 0; j < graph->nodes[i].edges_size; j++)
		{
			printf("%d (%d) ", graph->nodes[i].edges[j].to, graph->nodes[i].edges[j].cap);
		}
		if (graph->start_output_id == graph->nodes[i].id)
			printf(" <= start");
		if (graph->end_input_id == graph->nodes[i].id)
			printf(" <= end");


		printf("\n");
		i++;
	}
}
#endif

void	generate_node(t_solve *s, t_ek_graph *graph)
{
	int			i;

	i = 0;
	while (i < graph->nodes_size)
	{
		graph->nodes[i].id = i;
		graph->nodes[i].edges = malloc(sizeof(t_ek_edge) * (s->rooms[i / 2].links_size + 1));
		if (graph->nodes[i].edges == NULL)
			error_exit(MALLOC_ERR);
		graph->nodes[i].edges_size = 0;
		i++;
	}
	//input node and output node
	i = 0;
	while (i < graph->nodes_size)
	{
		if (i % 2 == 0) //input
		{
			graph->nodes[i].edges[0].to = i + 1;	
			graph->nodes[i].edges[0].cap = 1;
			graph->nodes[i].edges[0].rev = 0;
			graph->nodes[i].edges[0].from = -1;
			graph->nodes[i].edges[0].is_rev = 0;
			graph->nodes[i].edges_size++;
			//rev
			graph->nodes[i + 1].edges[0].to = i;	
			graph->nodes[i + 1].edges[0].cap = 0;
			graph->nodes[i + 1].edges[0].rev = 0;
			graph->nodes[i + 1].edges[0].from = -1;
			graph->nodes[i + 1].edges[0].is_rev = 1;
			graph->nodes[i + 1].edges_size++;
		}
		i++;
	}
	//links
	i = 0;
	int 		link_index;
	int			to_index;
	t_ek_node	*node_ptr;
	t_ek_node	*rev_ptr;

	while (i < s->rooms_size)
	{
		//printf("room: %d link size: %d\n", s->rooms[i].id, s->rooms[i].links_size);
		link_index = 0;
		//each link
		while (link_index < s->rooms[i].links_size)
		{
			//output
			node_ptr = &graph->nodes[i * 2 + 1];
			to_index = s->rooms[i].links[link_index];
			to_index *= 2;//fix input;
			node_ptr->edges[node_ptr->edges_size].to = to_index;
			node_ptr->edges[node_ptr->edges_size].cap = 1;
			node_ptr->edges[node_ptr->edges_size].from = -1;
			node_ptr->edges[node_ptr->edges_size].is_rev = 0;

			rev_ptr = &graph->nodes[to_index];
			
			//input
			to_index = node_ptr->id;
			rev_ptr->edges[rev_ptr->edges_size].to = to_index;
			rev_ptr->edges[rev_ptr->edges_size].cap = 0;
			rev_ptr->edges[rev_ptr->edges_size].from = -1;
			rev_ptr->edges[rev_ptr->edges_size].is_rev = 1;

			//each rev index
			node_ptr->edges[node_ptr->edges_size].rev = rev_ptr->edges_size;
			rev_ptr->edges[rev_ptr->edges_size].rev = node_ptr->edges_size;
			
			node_ptr->edges_size++;
			rev_ptr->edges_size++;

			link_index++;
		}
		i++;
	}
}

void	set_start_node(t_solve *s, t_ek_graph *graph)
{
	graph->start_input_id = s->start_id * 2;
	graph->start_output_id = s->start_id * 2 + 1;
	graph->end_input_id = s->end_id * 2;
	graph->end_output_id = s->end_id * 2 + 1;
}

void	generate_graph(t_map *map, t_solve *s, t_ek_graph *graph)
{
	//printf("----- generate graph -----\n");
	(void)map;

	//room => node, link => edge
	//edge * 2(in, out)
	graph->nodes_size = s->rooms_size * 2;
	//node * 2(rev) + edge * 2(both_side) * 2(rev)
	graph->edges_size = s->rooms_size * 2 + s->all_links_size * 2 * 2;

	//printf("%d\n", graph->nodes_size);
	//printf("%d\n", graph->edges_size);

	graph->nodes = malloc(sizeof(t_ek_node) * graph->nodes_size);
	if (graph->nodes == NULL)
		error_exit(MALLOC_ERR);
	generate_node(s, graph);
	set_start_node(s, graph);
	//show_graph(graph);
}
