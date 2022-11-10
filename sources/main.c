/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:46:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/10 19:13:49 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "parse.h"
#include "solve.h"
#include <unistd.h>

int		main(int argc, char** argv)
{
	t_byte	options;
	t_map	map;
	int		ret;
	char	*line;

	if (argc > 1)
	{
		options = retrieve_options(argc, argv, ARG_OPTIONS);
		if (options & HELP_OPTION)
		{
			ft_putstr_fd(HELP_MSG, STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}

	ft_bzero(&map, sizeof(t_map));

	queue_constructor(&map.line_queue);
	ret = 1;
	while (ret == 1)
		ret = parse_line(&map);

	while (queue_size(&map.line_queue) != 0)
	{
		line = (char*)queue_front(&map.line_queue);
		ft_putendl_fd(line, STDOUT_FILENO);
		free(line);
		queue_pop(&map.line_queue);
	}

	solve(&map);
	
	return (EXIT_SUCCESS);
}
