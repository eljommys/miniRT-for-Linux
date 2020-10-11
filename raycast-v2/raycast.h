#ifndef RAYCAST_H
# define RAYCAST_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_PR 2
# define BUT_PR 4
# define BUT_RE 5
# define MOT_NT 6
# define CLI_MG 33

# define MK_KEY_PR 1L << 0
# define MK_BUT_PR 1L << 2
# define MK_BUT_RE 1L << 3
# define MK_PTR_MO 1L << 6
# define CL_CLOSE 3

# define KEY_ESC	0xff1b
# define KEY_W		0x0077
# define KEY_A		0x0061
# define KEY_S		0x0073
# define KEY_D		0x0064
# define KEY_SPA	0x0020
# define KEY_CTR	0xffe3

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux-master/mlx.h"

typedef struct	s_mouse{
	int		x;
	int		y;
	double	speed;
}				t_mouse;

typedef struct	s_coord{
	int		x;
	int		y;
	int		aux_x;
	int		aux_y;
}				t_coord;

typedef struct	s_rot{
	double	z;
	double	y;
	double	cos_y;
	double	sin_y;
	double	cos_z;
	double	sin_z;
	int		Vd[3];
}				t_rot;

typedef struct s_screen{
	int		x;
	int		y;
	int		fov;
	double	dist;
}				t_screen;

typedef struct {
	p[3];
	p_conv[3];
};


typedef struct	s_data{

	t_mouse		mouse;
	t_coord		coord;
	t_rot		rot;
	t_screen	screen;

	void		*id;
	void		*win_id;

	int			key;
	int			button;

	double 		Vn[3];

	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	double		**p;
	double		**p_conv;
}				t_data;

void 	calculate_rotation(t_data *param);
void	show_pov(t_data *param);
void	create_cube(t_data *param, double *p1, double *p2);

#endif
