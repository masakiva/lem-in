#include "libft.h"
#include "parse.h"
#include "../headers/ft_queue.h"
#include "../headers/solve.h"
#include "../headers/visualizar.h"

void drawCircle(int radius, int x1, int y1, t_visualizar *v, int color)
{
	int x, y;
	int dx, dy;

	for(y = 0 + y1 - radius; y < y1 + radius; y++)
	{
		for(x = 0 + x1 - radius; x < x1 + radius; x++)
		{
			dx = (int)x - (int)x1;
			dy = (int)y - (int)y1;

			if((dx * dx) + (dy * dy) <= radius * radius)
			{
				protected_pixel_put(v, x, y, color);
			}
		}
	}
}

void drawLineTwoPixels2(int xs, int ys, int xe, int ye, t_visualizar *v, int color)
{
	int x, y;
	int dx, dy;
	double rad;
	int length;
	int l;
	int move_by_time = (int)(get_time(v->first_time) * 20);

	dx = xe - xs;
	dy = ye - ys;

	length = sqrt(dx * dx + dy * dy);

	rad = atan2(dy, dx);

 	for(l = 0; l < length; l++)
	{
    	x = xs + l * cos(rad);
    	y = ys + l * sin(rad);
		//if ((l + (int)(get_time(v->first_time) * 20) % 20) % 20 < 10)
		if (((l + move_by_time) % 20) % 20 < 10)
			protected_pixel_put(v, x, y, BLACK);
		else
			protected_pixel_put(v, x, y, color);
    }
}

void drawLineTwoPixels(int xs, int ys, int xe, int ye, t_visualizar *v, int color)
{
	int x, y;
	int dx, dy;
	double rad;
	int length;
	int l;

	dx = xe - xs;
	dy = ye - ys;

	length = sqrt(dx * dx + dy * dy);

	rad = atan2(dy, dx);

 	for(l = 0; l < length; l++)
	{
    	x = xs + l * cos(rad);
    	y = ys + l * sin(rad);
		protected_pixel_put(v, x, y, color);
    }
}
