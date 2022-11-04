/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:17 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/04 11:28:16 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	space(t_state_machine* machine, char* line)
{
	if (*line == '#')
	{
		machine->state = HASH;
		printf("hash\n");
	}
	if (*line == '\0')
		machine->state = END;
}

void	letter(t_state_machine* machine, char* line)
{
	(void)machine;
	(void)line;
}

void	hash(t_state_machine* machine, char* line)
{
	machine->state = SPACE;
	(void)line;
}

void	extract_line_infos(char* line)
{
	static t_parse	process[NB_STATES - 1] = {space, letter, hash};
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(t_state_machine));
	while (machine.state != END)
	{
		process[machine.state](&machine, line);
		line++;
	}
}

int		parse_line(void)
{
	char*	line;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &line);
	if (ret == ERROR)
		printf("gnl err %d\n", GNL_ERR);
	else
	{
		extract_line_infos(line);
		printf("line = %s\n", line);
		free(line);
	}

	return (ret);
}

int		main(void)
{
	int		ret;

	ret = 1;
	while(ret == 1)
	{
		ret = parse_line();
	}

	return (EXIT_SUCCESS);
}
