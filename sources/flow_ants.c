#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	flow_ant_init(t_solve *s, t_path_manager *m)
{
	int		i;
	t_list	*node;

	s->ant_manager.ants = malloc(sizeof(t_ant) * s->ant_size);
	if (s->ant_manager.ants == NULL)
		error_exit(MALLOC_ERR);
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
		if (node == NULL)
			error_exit(MALLOC_ERR);
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
		if (path->use_num && m->ants_count < s->ant_size)
		{
			m->ants[m->ants_count].path = path;//regist ants => queue
			queue_push(q, &(m->ants[m->ants_count]));
			m->ants_count++;
			path->use_num--;
		}
		node = node->next;
	}
}

void	put_ants(t_ant *ant, t_solve *s)
{
	ft_putstr_fd("L", 1);
	ft_putnbr_fd(ant->id, 1);
	ft_putstr_fd("-", 1);
	ft_putstr_fd(s->rooms[ant->path->root[ant->path_position]].name_ptr, 1);
	ft_putstr_fd(" ", 1);
}

void	pop_ants(t_solve *s, t_ek_graph *graph, t_queue *current_q, t_queue *next_q)
{
	t_ant	*ant;

	while (1)
	{
		ant = (t_ant *)queue_front(current_q);
		queue_pop(current_q);
		put_ants(ant, s);
		ant->path_position++;
		if (ant->path_position != ant->path->root_size)
			queue_push(next_q, ant);
		if (queue_size(current_q) != 0)
			ft_putstr_fd(" ", 1);
		else
		{
			ft_putstr_fd("\n", 1);
			break ;
		}
	}
	(void)graph;
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
		pop_ants(s, graph, current_q, next_q);
		start_ants(s, next_q);
	}
	queue_destructor(current_q);
	queue_destructor(next_q);
	(void)graph;
}

void	put_map(t_map *map)
{
	char	*line;

	while (queue_size(&map->line_queue) != 0)
	{
		line = (char*)queue_front(&map->line_queue);
		if (ft_putendl_fd(line, 1) != WRITE_SUCCESS)
			error_exit(WRITE_ERR);
		free(line);
		queue_pop(&map->line_queue);
	}
}

void	flow_ants(t_map *map, t_solve *s, t_ek_graph *graph)
{
	put_map(map);
	flow_ant_init(s, &(graph->path_manager));
	flow_ants_execute(s, graph);
	(void)map;

	lem_in_visualizar(map, s, graph);
}
