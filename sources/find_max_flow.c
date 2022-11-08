#include "libft.h"
#include "parse.h"
#include "../headers/solve.h"

#define INF 1000000000

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

//再帰的に帰るならmallocして詰めて帰る。
void	follow_root_recurse(int current_id, int end_id, t_ek_graph *graph)
{
	int i = 0;

	if (current_id == end_id)
	{
		printf("end\n");
		return ;
	}

	int flag;

	while (i < graph->nodes[current_id].edges_size)
	{
		flag = 1;
		if (current_id % 2 == 1)

		if (graph->nodes[current_id].edges[i].cap == 0)
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
	
	printf("start\n");
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
		ret = flow_dfs(graph->start_output_id, graph->end_input_id, 1, graph);

		follow_root(map, s, graph);
		printf("dfs %d\n", ret);
		if (ret == 0)
			break;
	}
}
