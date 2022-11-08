/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:46:12 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/08 09:34:27 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "parse.h"
#include "solve.h"
#include <stdio.h>

int		main(void)
{
	int		ret;
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	ret = 1;
	while (ret == 1)
	{
		ret = parse_line(&map);
	}

	//solve(&map);
	
	return (EXIT_SUCCESS);
}
