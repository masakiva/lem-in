#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void	set_string_to_buffer(char **head, char *set)
{
	char	*pos;

	pos = *head;
	while (*set)
	{
		*(--pos) = *set;
		set++;
	}
	*head = pos;
}

void	set_coordinate(t_visualizar *v, int x, int y)
{
	int	sign;

	x = (x - v->world_x) / v->display_ratio;
	y = (y - v->world_y) / v->display_ratio;

	v->str_buffer_head = v->str_buffer + STR_BUFFER_SIZE;
	*v->str_buffer_head = '\0';

	*(--v->str_buffer_head) = ')';

	sign = 1;
	if (y < 0)
		sign = -1;
	while (*(v->str_buffer_head) == ')' || y != 0)
	{
		*(--v->str_buffer_head) = y % 10 * sign + '0';
		y = y / 10;
	}
	if (sign == -1)
		*(--v->str_buffer_head) = '-';
	*(--v->str_buffer_head) = ':';
	*(--v->str_buffer_head) = 'y';
	*(--v->str_buffer_head) = ' ';

	sign = 1;
	if (x < 0)
		sign = -1;
	while (*(v->str_buffer_head) == ' ' || x != 0)
	{
		*(--v->str_buffer_head) = x % 10 * sign + '0';
		x = x / 10;
	}
	if (sign == -1)
		*(--v->str_buffer_head) = '-';
	*(--v->str_buffer_head) = ':';
	*(--v->str_buffer_head) = 'x';
	*(--v->str_buffer_head) = '(';
}

/*
void	put_turn(t_visualizar *v)
{

}*/

void	put_time(t_visualizar *v)
{
	int		time = get_time(v->first_time);

	v->str_buffer_head = v->str_buffer + STR_BUFFER_SIZE;
	*v->str_buffer_head = '\0';

	int sign = 1;

	if (time < 0)
		sign = -1;
	while (*(v->str_buffer_head) == '\0' || time != 0)
	{
		*(--v->str_buffer_head) = time % 10 * sign + '0';
		time = time / 10;
	}
	if (sign == -1)
		*(--v->str_buffer_head) = '-';
	set_string_to_buffer(&v->str_buffer_head, ":emit");

	put_buffer(v, 30, 60);
}

void	put_info(t_visualizar *v)
{
	put_time(v);
}

void	put_buffer(t_visualizar *v, int x, int y)
{
	mlx_string_put(v->mlx_ptr, v->win_ptr, x, y, LIME, v->str_buffer_head);	
}
