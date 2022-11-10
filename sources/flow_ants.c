#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

void	flow_ant_init(t_solve *s, t_path_manager *m)
{
	int		i;
	t_list	*node;

	s->ant_manager.ants = malloc(sizeof(t_ant) * s->ant_size);
	i = 0;
	while (i < s->ant_size)
	{
		s->ant_manager.ants[i].id = i + 1;
		s->ant_manager.ants[i].path_position = 1;
		i++;
	}
	i = 0;
	s->ant_manager.path_list = NULL;
	while (i < m->current_path_set->paths_size)
	{
		node = ft_lstnew(m->current_path_set->paths[i]);
		ft_lstadd_back(&(s->ant_manager.path_list), node);
		i++;
	}
}

void	start_ants(t_solve *s, t_queue *q)
{
	t_ant_manager	*m = &s->ant_manager;
	t_list			*node;
	t_path			*path;
	
	node = m->path_list;
	while (node)
	{
		path = (t_path *)node->content;
		if (path->use_num)
		{
			m->ants[m->ants_count].path = path;//regist ants => queue
			//queue_push(q, (void *)(long long)m->ants_count);
			queue_push(q, &(m->ants[m->ants_count]));
			m->ants_count++;
			path->use_num--;
		}
		node = node->next;
	}
}

void	pop_ants(t_solve *s, t_ek_graph *graph, t_queue *current_q, t_queue *next_q)
{
	t_ant	*ant;

	while (queue_size(current_q) != 0)
	{
		ant = (t_ant *)queue_front(current_q);
		queue_pop(current_q);
		printf("L");
		printf("%d-", ant->id);
		printf("%s ", s->rooms[ant->path->root[ant->path_position]].name_ptr);
		ant->path_position++;
	
		if (ant->path_position != ant->path->root_size)
			queue_push(next_q, ant);
	}
	printf("\n");
	(void)s;
	(void)graph;
	(void)next_q;
}

void	flow_ants_execute(t_solve *s, t_ek_graph *graph)
{
	t_queue		tmp_queue1;
	t_queue		tmp_queue2;
	t_queue		*current_q = &tmp_queue1;
	t_queue		*next_q = &tmp_queue2;
	t_queue		*tmp_q;

	s->ant_manager.ants_count = 0;
	s->ant_manager.ants_limit = s->ant_size;

	queue_constructor(current_q);
	queue_constructor(next_q);
	start_ants(s, next_q);

	while (queue_size(next_q) != 0)
	{
		tmp_q = next_q;
		next_q = current_q;
		current_q = tmp_q;
		//pop_ants(s, graph, q);
		pop_ants(s, graph, current_q, next_q);
		//queue_pop(q);
		
		//printf("x: %d\n", ant->id);
		start_ants(s, next_q);
	}
	queue_destructor(current_q);
	queue_destructor(next_q);
	(void)graph;
}


void	flow_ants(t_map *map, t_solve *s, t_ek_graph *graph)
{
	flow_ant_init(s, &(graph->path_manager));
	flow_ants_execute(s, graph);
	(void)map;
	(void)s;
	(void)graph;
}
