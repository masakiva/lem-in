#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

#define INF 1000000000

void	max_flow_init(t_ek_graph *graph)
{
	graph->bfs_used = malloc(sizeof(int) * graph->nodes_size);
	graph->bfs_node_from = malloc(sizeof(int) * graph->nodes_size);
	graph->bfs_edge_from = malloc(sizeof(int) * graph->nodes_size);

	graph->root_buffer_begin = malloc(sizeof(int) * graph->nodes_size);
	graph->path_manager.path_set_list_size = 0;
	graph->path_manager.path_set_list = NULL;
}

void	used_set_zero(t_ek_graph *graph)
{
	int		i;

	i = 0;
	while (i < graph->nodes_size)
	{
		graph->bfs_used[i] = 0;
		graph->bfs_node_from[i] = 0;
		graph->bfs_edge_from[i] = 0;
		i++;
	}
}

void	check_flow(t_ek_graph *graph, int start_id, int current_id)
{
	int			prev_step;
	int			selected_edge;
	t_ek_edge	*edge;

	while (1)
	{
		if (start_id == current_id)
			return ;
		prev_step = graph->bfs_node_from[current_id];
		selected_edge = graph->bfs_edge_from[current_id];
		edge = &(graph->nodes[prev_step].edges[selected_edge]);
		//cap --
		edge->cap += -1;
		graph->nodes[edge->to].edges[edge->rev].cap += 1;
		
		current_id = prev_step;
	}
}

int		flow_bfs(int from, int end, t_ek_graph *graph)
{
	t_queue		q_tmp;
	t_queue		*q = &q_tmp;

	queue_constructor(q);
	queue_push(q, (void *)((long long)from));

	int 		id;
	int			i;
	t_ek_edge	*edge;

	while (queue_size(q) != 0)
	{
		id = (int)queue_front(q);
		queue_pop(q);
		i = 0;
		while (i < graph->nodes[id].edges_size)
		{
			edge = &(graph->nodes[id].edges[i]);
			if (graph->bfs_used[edge->to] == 0 && edge->cap > 0)
			{
				graph->bfs_used[edge->to] = 1;
				graph->bfs_node_from[edge->to] = id;
				graph->bfs_edge_from[edge->to] = i;
				if (edge->to == end)
				{
					check_flow(graph, from, edge->to);
					queue_destructor(q);
					return 1;
				}
				queue_push(q, (void *)((long long)edge->to));
			}
			i++;
		}
	}
	queue_destructor(q);
	return 0;
}

void	set_root_to_buffer(int	current_id, t_ek_graph *graph)
{
	if (graph->root_buffer_end != graph->root_buffer_begin)
	{
		if (current_id % 2 != 0)
			return ;
	}
	*graph->root_buffer_end = current_id / 2;
	graph->root_buffer_end++;
}

void	show_buffer(t_ek_graph *graph, t_solve *s)
{
	int		*head = graph->root_buffer_begin;
	int		*end = graph->root_buffer_end;

	while (head != end)
	{
		printf("buffer %s\n", s->rooms[*head].name_ptr);
		head++;
	}
}

void	allocate_path(t_ek_graph *graph, t_solve *s)
{
	int		*head = graph->root_buffer_begin;
	int		*end = graph->root_buffer_end;
	t_path	*path = malloc(sizeof(path));
	int		i = 0;

	path->root = malloc(sizeof(int) * (end - head));

	while (head != end)
	{
		path->root[i] = *head;
		head++;
		i++;
	}
	path->root_size = i;

	int 	index = graph->path_manager.current_path_set->paths_size;

	graph->path_manager.current_path_set->paths[index] = path;
	index++;
	graph->path_manager.current_path_set->paths[index] = NULL;
	graph->path_manager.current_path_set->paths_size = index;

	//i = 0;
	//while (i < path->root_size)
	//{
	//	printf("%d %s\n", path->root[i], s->rooms[path->root[i]]);
	//	i++;
	//}
	(void)s;
}

//再帰的に帰るならmallocして詰めて帰る。
void	follow_root_recurse(int current_id, int start_id, int end_id, t_ek_graph *graph, t_solve *s)
{
	int i = 0;

	if (current_id == end_id)
	{
		//printf("> %d\n", current_id);
		//printf("> real name [%s]\n", s->rooms[current_id / 2].name_ptr);
		set_root_to_buffer(current_id, graph);
		show_buffer(graph, s);
		allocate_path(graph, s);
		printf("[ ---- end ---- ]\n");
		return ;
	}

	while (i < graph->nodes[current_id].edges_size)
	{
		if (graph->nodes[current_id].edges[i].cap == 0
			&& graph->nodes[current_id].edges[i].is_rev == 0)
		{
			if (current_id == start_id)
			{
				printf("[ ---- start ---- ]\n");
				graph->root_buffer_end = graph->root_buffer_begin;
			}
			set_root_to_buffer(current_id, graph);

			//printf("> %d\n", current_id);
			//printf("> real name [%s]\n", s->rooms[current_id / 2].name_ptr);
			follow_root_recurse(graph->nodes[current_id].edges[i].to, start_id, end_id, graph, s);
		}
		i++;
	}
}

void	follow_root(t_map *map, t_solve *s, t_ek_graph *graph)
{
	(void)map;
	t_path_set	*path_set = malloc(sizeof(t_path_set));
	t_list		*list_node;

	list_node = ft_lstnew(path_set);
	ft_lstadd_back(&(graph->path_manager.path_set_list), list_node);
	
	graph->path_manager.path_set_list_size++;
	graph->path_manager.current_path_set = path_set;
	//path_set
	path_set->paths = malloc(sizeof(t_path *) * (graph->path_manager.path_set_list_size + 1));
	path_set->paths_size = 0;

	follow_root_recurse(graph->start_output_id, graph->start_output_id, graph->end_input_id, graph, s);
}

void	find_max_flow(t_map *map, t_solve *s, t_ek_graph *graph)
{
	int		ret;

	(void)map;
	(void)s;
	max_flow_init(graph);
	//if (1)
	while (1)
	{
		used_set_zero(graph);
		ret = flow_bfs(graph->start_output_id, graph->end_input_id, graph);
		printf("\nfind new root => %d\n", ret);
		if (ret == 0)
			break;
		follow_root(map, s, graph);
	}
}
