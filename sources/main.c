/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:46:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/09 11:28:22 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "parse.h"
#include "solve.h"
#include <unistd.h>

int		main(int argc, char** argv)
{
	int		ret;
	t_map	map;
	t_byte	options;

	if (argc > 1)
	{
		options = retrieve_options(argc, argv, ARG_OPTIONS);
		if (options & HELP_OPTION)
		{
			ft_putstr_fd("[lem-in] usage: \n", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}
	ft_bzero(&map, sizeof(t_map));
	ret = 1;
	while (ret == 1)
	{
		ret = parse_line(&map);
	}

	solve(&map);
	
	return (EXIT_SUCCESS);
}
