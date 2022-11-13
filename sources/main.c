/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:46:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 20:24:28 by mvidal-a         ###   ########.fr       */
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

	ft_bzero(&map, sizeof(t_map));

	if (argc > 1)
	{
		options = retrieve_options(argc, argv, ARG_OPTIONS);
		if (options & HELP_OPTION)
		{
			if (ft_putstr_fd(HELP_MSG, STDOUT_FILENO) != SUCCESS)
				error_exit(WRITE_ERR);
			return (EXIT_SUCCESS);
		}
		if (options & VISUAL_OPTION)
			map.visual = TRUE;
	}

	queue_constructor(&map.line_queue);
	ret = 1;
	while (ret == 1)
		ret = parse_line(&map);

	check_input(&map);

	solve(&map);
	return (EXIT_SUCCESS);
}
