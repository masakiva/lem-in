/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:22:17 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/04 11:57:54 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char*	character(t_state_machine* machine, char* line)
{
	if (*line == '#')
	{
		machine->state = HASH;
		printf("hash\n");
		line++;
	}
	if (ft_isdigit(*line))
		machine->state = DIGIT;
	if (*line == '\0')
		machine->state = END;
	return (line);
}

int		iscoord(char* line)
{
	while (ft_isdigit(*line))
		line++;
	if (*line == ' ')
	{
		line++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ' ')
		{
			line++;
			while (ft_isdigit(*line))
				line++;
			if (*line == '\0')
				return (TRUE);
		}
	}
	return (FALSE);
}

int		islink(char* line)
{
	while (ft_isdigit(*line))
		line++;
	if (*line == '-')
	{
		line++;
		while (ft_isdigit(*line))
			line++;
		if (*line == '\0')
			return (TRUE);
	}
	return (FALSE);
}

char*	digit(t_state_machine* machine, char* line)
{
	if (iscoord(line))
		printf("ROOM\n");
	else if (islink(line))
		printf("LINK\n");
	else
		printf("err\n");
	machine->state = END;
	return (line);
}

char*	hash(t_state_machine* machine, char* line)
{
	if (*line == '#')
	{
		machine->state = DOUBLE_HASH;
		printf("double hash\n");
		line++;
	}
	else // it's a comment
		machine->state = END;
	return (line);
}

char*	double_hash(t_state_machine* machine, char* line)
{
	if (ft_strcmp(line, "start") == 0)
		printf("START\n");
	else if (ft_strcmp(line, "end") == 0)
		printf("END\n");
	else
		printf("err\n");
	machine->state = END;
	return (line);
}

void	extract_line_infos(char* line)
{
	static t_parse	process[NB_STATES - 1] = {character, digit, hash,
		double_hash};
	t_state_machine	machine;

	ft_bzero(&machine, sizeof(t_state_machine));
	while (machine.state != END)
	{
		line = process[machine.state](&machine, line);
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
