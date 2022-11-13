#ifndef VISUALIZAR_H
#define VISUALIZAR_H

#include "parse.h"
#include "solve.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define WINDOW_WIDHT	1000
#define WINDOW_HEIGHT	1000

#define EVENT_EXIT		17

// ====== mac =====
# define KEY_RIGHT	124
# define KEY_LEFT	123
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_ESC	53

# define KEY_U		32
# define KEY_M		46
# define KEY_1		18
# define KEY_2		19
# define KEY_3		20
# define KEY_4		21
# define KEY_5		23
# define KEY_6		22
# define KEY_7		26
# define KEY_W		13
# define KEY_S		1
# define KEY_A		0
# define KEY_D		2

# define KEY_N		45
# define KEY_B		11
# define KEY_R		15
# define KEY_P		35
# define KEY_F		3

# define BLACK		0x000000
# define LIME		0x00FF00
# define BLUE		0x2121DE
//# define BLUE		0x0000FF
# define WHITE		0xFFFFFF

# define YELLOW		0xFFFF00
# define TUMBLEWEED	0xDEA185

# define RED		0xFD0000
# define PINK		0xFFB8FF
# define CYAN		0x00FFFF
# define ORANGE		0xFFB852
# define DARK_BLUE	0x1919A6

# define THIN_LIME	0xe3fed2

# define LIME2		0x1bff80
# define LIME3		0x99ff99
# define LIME4		0x6bb36b

# define VISUAL_PRINTF	0
# define STR_BUFFER_SIZE 100
# define ZOOM_STEP		10

# define FLOW_SPEED		1
# define FRAME_RATIO	5000

# define CYCLE_PER_SEC 2700000000

typedef struct	s_v_node
{
	int		id;
	int		v_x;
	int		v_y;
}				t_v_node;

typedef struct	s_visualizar
{
	//mlx
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_addr;
	int		img_bit_per_pixel;
	int		img_line_lenght;

	//node
	t_v_node	*nodes;

	int			nodes_size;

	//display
	int			display_ratio;
	int			world_x;
	int			world_y;
	int			mouse_x;
	int			mouse_y;
	int			mouse_button1_pressed;

	//game
	int			turn;
	int			frame;
	int			move_frame;
	int			end_ants;
	int			start_ants;
	int			is_flow;
	
	//tmp_buffer
	char		str_buffer[STR_BUFFER_SIZE + 1];
	char		*str_buffer_head;

	//time
	unsigned long long	first_time;

	//lem-member
	t_map		*map;
	t_solve		*s;
	t_ek_graph	*graph;
}				t_visualizar;

void	lem_in_visualizar(t_map *map, t_solve *s, t_ek_graph *graph);

//draw sharp
void drawCircle(int radius, int x1, int y1, t_visualizar *v, int color);
void drawLineTwoPixels(int xs, int ys, int xe, int ye, t_visualizar *v, int color);
void drawLineTwoPixels2(int xs, int ys, int xe, int ye, t_visualizar *v, int color, int ox, int oy);

//info
void	set_coordinate(t_visualizar *v, int x, int y);
void	put_buffer(t_visualizar *v, int x, int y);
void	put_info(t_visualizar *v);

//pixel
void	fill_black(t_visualizar *v);
void	protected_pixel_put(t_visualizar *v, int x, int y, int color);
void	my_mlx_pixel_put(t_visualizar *v, int x, int y, int color);

//time
unsigned long long get_cycle();
double get_time(unsigned long long int b);

//ant
void	vis_put_ants(t_visualizar *v);
void	vis_put_ants_name(t_visualizar *v);
#endif
