#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"

void	flow_ant_init(t_solve *s)
{
	int		i;

	s->ant_manager.ants = malloc(sizeof(t_ant) * s->ant_size);
	i = 0;
	while (i < s->ant_size)
	{
		s->ant_manager.ants[i].id = i;
		s->ant_manager.ants[i].path_position = 0;
		i++;
	}
}

void	flow_ants(t_map *map, t_solve *s, t_ek_graph *graph)
{
	(void)map;
	(void)s;
	(void)graph;
}
