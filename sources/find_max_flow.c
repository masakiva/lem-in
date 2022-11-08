#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

#define INF 1000000000

void	max_flow_init(t_ek_graph *graph)
{
	graph->used = malloc(sizeof(int) * graph->nodes_size);
	graph->bfs_used = malloc(sizeof(int) * graph->nodes_size);
	graph->bfs_node_from = malloc(sizeof(int) * graph->nodes_size);
	graph->bfs_edge_from = malloc(sizeof(int) * graph->nodes_size);
}

void	used_set_zero(t_ek_graph *graph)
{
	int		i;

	i = 0;
	while (i < graph->nodes_size)
	{
		graph->used[i] = 0;
		graph->bfs_used[i] = 0;
		graph->bfs_node_from[i] = 0;
		graph->bfs_edge_from[i] = 0;
		i++;
	}
}

int		flow_dfs(int from, int end, int cap, t_ek_graph *graph)
{
	int			i;
	t_ek_edge	*edge;

	if (from == end)
		return cap;
	graph->used[from] = 1;
	i = 0;
    //for (edge &e:G[v])
	printf("%d\n", from);
	while (i < graph->nodes[from].edges_size)
	{
		edge = &(graph->nodes[from].edges[i]);
        //if(!used[e.to] && e.cap > 0){
		if (graph->used[edge->to] == 0 && edge->cap > 0)
		{
            //int d = flow_dfs(e.to, t, min(mincap, e.cap));
			int d = flow_dfs(edge->to, end, 1, graph);
            if (d > 0)
			{
                //e.cap -= d;
				edge->cap -= d;
                //G[e.to][e.rev].cap += d;
				graph->nodes[edge->to].edges[edge->rev].cap += d;
                return d;
            }
        }	
		i++;
	}
	return 0;
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

int		flow_bfs(int from, int end, int cap, t_ek_graph *graph)
{
	t_queue		q_tmp;
	t_queue		*q = &q_tmp;

	queue_constructor(q);
	queue_push(q, (void *)((long long)from));

	int 		id;
	int			i;
	t_ek_edge	*edge;

	printf("from %d\n", from);
	while (queue_size(q) != 0)
	{
		id = (int)queue_front(q);
		queue_pop(q);
		printf("id => %d real num %d\n", id, id / 2);

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
					printf("=====> goal\n");
					check_flow(graph, from, edge->to);
					queue_destructor(q);
					return 1;
				}
				queue_push(q, (void *)((long long)edge->to));
			}
			i++;
		}

	}
	(void)cap;
	queue_destructor(q);
	return 0;
}

//再帰的に帰るならmallocして詰めて帰る。
void	follow_root_recurse(int current_id, int end_id, t_ek_graph *graph)
{
	int i = 0;

	if (current_id == end_id)
	{
			printf("%d\n", current_id);
		printf(">>> end\n");
		return ;
	}

	int flag;

	while (i < graph->nodes[current_id].edges_size)
	{
		flag = 1;
		if (graph->nodes[current_id].edges[i].cap == 0 && graph->nodes[current_id].edges[i].is_rev == 0)
		{
			printf("%d\n", current_id);
			follow_root_recurse(graph->nodes[current_id].edges[i].to, end_id, graph);
		}
		i++;
	}
}

void	follow_root(t_map *map, t_solve *s, t_ek_graph *graph)
{
	(void)map;
	(void)s;
	
	printf(">>> start\n");
	follow_root_recurse(graph->start_output_id, graph->end_input_id, graph);
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
		//ret = flow_dfs(graph->start_output_id, graph->end_input_id, 1, graph);
		ret = flow_bfs(graph->start_output_id, graph->end_input_id, 1, graph);
		printf("find new root => %d\n", ret);
		if (ret == 0)
			break;
		follow_root(map, s, graph);
	}
}
