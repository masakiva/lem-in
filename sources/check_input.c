/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:24:41 by mvidal-a          #+#    #+#             */
/*   Updated: 2022/11/13 20:24:53 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	check_input(t_map* map)
{
	if (map->nb_ants <= 0)
		error_exit(INPUT_MISSING);
	else if (map->rooms == NULL)
		error_exit(ROOMS_LINKS_MISSING);
	else if (map->links == NULL)
		error_exit(LINKS_MISSING);
}

