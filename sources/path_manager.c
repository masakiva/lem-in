#include "libft.h"
#include "parse.h"
#include "../headers/solve.h"

void	display_struct_path(t_path *path_ptr, t_solve *s)
{
	(void)path_ptr;
	int i = 0;
	int num;

	while (i < path_ptr->root_size)
	{
		num = path_ptr->root[i];
		printf("path: [%s]\n", s->rooms[num / 2].name_ptr);
		i++;
	}
}
