#ifndef RAYMARCHING_H
# define RAYMARCHING_H

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

typedef struct	s_screen{
	int		x;
	int		y;
	int		fov;
	double	dist;
}				t_screen;

typedef struct	s_camera{
	double	O[3];
	double	P[3];
	double	Vn[3];
	double	Vx[3];
	double	Vy[3];
	double	rot_z;
	double	rot_y;
	double	ray[3];
	double	ray_module;
	double	pixel[3];
}				t_camera;

typedef struct	s_image{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_sphere{
	double	O[3];
	double	r;
	int		color;
}				t_sphere;

typedef struct	s_light{
	double	O[3];
	int		color;
}				t_light;

typedef struct	s_data{
	void		*id;
	void		*win_id;
	int			key;
	int			button;
	t_mouse		mou;
	t_coord		crd;
	t_screen	scr;
	t_camera	cam;
	t_image		img;
	t_sphere	**sp;
	t_light		**l;
}				t_data;

void	calculate_vectors(t_data *def);
void 	calculate_rotation(t_data *param);

t_sphere	**add_sp(t_sphere **sp, double *O, double r);
t_light		**add_l(t_light **l, double *O);

/*
**	Fundiones de prueba
*/

void	show_camera(t_data *param);
void	show_pov(t_data *param);
void	show_sp(t_data *param);

#endif
