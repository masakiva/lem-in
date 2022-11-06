/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:17 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/06 18:49:08 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	extract_line_infos(char* line, t_map* map)
{
	static t_parse	process[NB_STATES - 1] = {character, roomname, hash,
		double_hash, start_end_line};
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(t_state_machine));
	machine.map = map;
	if (map->start_flag == TRUE || map->end_flag == TRUE)
		machine.state = START_END_LINE;
	while (machine.state != END)
	{
		line = process[machine.state](&machine, line);
	}
}

int		parse_line(t_map* map)
{
	char*	line;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &line);
	if (ret == ERROR)
		printf("gnl err %d\n", GNL_ERR);
	else
	{
		extract_line_infos(line, map);
		free(line);
	}

	return (ret);
}
