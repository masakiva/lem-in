/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:27:14 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/09 11:30:12 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_byte	check_arg_for_options(char *arg, char *op_chars)
{
	size_t	i;
	ssize_t	j;
	t_byte	options;

	options = 0;
	if (arg[0] == '-')
	{
		if (arg[1] == '-' && ft_strcmp(arg + 2, LONG_HELP_OPTION) == 0)
			options |= HELP_OPTION;
		else
		{
			i = 1;
			while (arg[i] != '\0')
			{
				j = ft_index(op_chars, arg[i]);
				if (j != NOT_FOUND && j < 8)
					options |= 0b00000001 << j;
				else
					return (0);
				i++;
			}
		}
	}
	return (options);
}

t_byte			retrieve_options(int argc, char **argv, char *op_chars)
{
	int		i;
	t_byte	cur_options;
	t_byte	options;

	i = 1;
	options = 0;
	while (i < argc)
	{
		cur_options = check_arg_for_options(argv[i], op_chars);
		if (cur_options == 0)
			break ;
		options |= cur_options;
		i++;
	}
	return (options);
}

