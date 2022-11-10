#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

/*
void	flow_ant_init(t_solve *s, t_path_manager *m)
{
	int		i;
	t_list	*node;

	s->ant_manager.ants = malloc(sizeof(t_ant) * s->ant_size);
	i = 0;
	while (i < s->ant_size)
	{
		s->ant_manager.ants[i].id = i;
		s->ant_manager.ants[i].path_position = 0;
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
			m->ants[m->ants_count].path = path;
			//queue_push(q, (void *)(long long)m->ants_count);
			queue_push(q, &(m->ants[m->ants_count]));
			m->ants_count++;
			path->use_num--;
		}
		node = node->next;
	}
}

void	flow_ants_execute(t_solve *s, t_ek_graph *graph)
{
	t_queue		tmp_queue;
	t_queue		*q = &tmp_queue;
	t_ant		*ant;

	s->ant_manager.ants_count = 0;
	s->ant_manager.ants_limit = s->ant_size;

	queue_constructor(q);
	start_ants(s, q);

	while (queue_size(q) != 0)
	{
		ant = (t_ant *)queue_front(q);
		queue_pop(q);
		
		printf("L")
		printf("x: %d\n", ant->id);
	}
	queue_destructor(q);
	(void)graph;
}
*/
void	flow_ants(t_map *map, t_solve *s, t_ek_graph *graph)
{
	//flow_ant_init(s, &(graph->path_manager));
	//flow_ants_execute(s, graph);
	(void)map;
	(void)s;
	(void)graph;
}
