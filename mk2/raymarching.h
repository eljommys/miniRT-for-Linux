/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:42:54 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/17 13:42:54 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define KEY_ENT	0xff0d

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux-master/mlx.h"
# include "gnl/get_next_line_bonus.h"
# include "libft/libft.h"

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

typedef struct	s_ray{
	double	V_o[3];
	double	V_l[3];
	double	O[3];
	double	O_prev[3];
	double	mod;
	int		obj_c;
	int		obj_n;
	int		ray_c;
	int		ray_rgb[3];
	int		ray_rgb_l[3];
	int		ray_rgb_o[3];
	double	intens;
}				t_ray;

typedef struct	s_camera{
	double	O[3];
	double	P[3];
	double	Vn[3];
	double	Vx[3];
	double	Vy[3];
	double	rot_z;
	double	rot_y;
	t_ray	ray;
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
	int		col;
}				t_sphere;

typedef struct	s_plane{
	double	O[3];
	double	v[3];
	int		col;
}				t_plane;

typedef struct	s_cylinder{
	double	O[3];
	double	v[3];
	double	h;
	double	d;
	int		col;
}				t_cylinder;

typedef struct	s_square{
	double	O[3];
	double	v[3];
	double	x[3];
	double	y[3];
	double	h;
	int		col;
}				t_square;

typedef struct	s_box{
	double	O[3];
	double	v[3];
	double	x[3];
	double	y[3];
	double	h;
	int		col;
}				t_box;

typedef struct	s_triangle{
	double	A[3];
	double	B[3];
	double	C[3];
	double	ab[3];
	double	ac[3];
	double	nor[3];
	int		col;
}				t_triangle;

typedef struct	s_light{
	double	O[3];
	int		col;
	int		rgb[3];
}				t_light;

typedef struct	s_data{
	void		*id;
	void		*win_id;
	int			key;
	int			button;
	int			reload;
	t_mouse		mou;
	t_coord		crd;
	t_screen	scr;
	t_camera	cam;
	t_image		img;
	t_sphere	**sp;
	t_plane		**pl;
	t_cylinder	**cy;
	t_square	**sq;
	t_box		**bx;
	t_triangle	**tr;
	t_light		**l;
	int			amb_l;
	int			amb_l_rgb[3];
}				t_data;

/*
**	input.c
*/

int		get_pos(int x, int y, t_data *param);
int		button_pressed(int button, int x, int y, t_data *param);
int		button_released(int button, int x, int y, t_data *param);
int		key_pressed(int keycode, t_data *param);

/*
**	misc/
*/

int		ft_loop(t_data *param);
int		ft_exit(t_data *param);
void	my_mlx_pixel_put(t_data *param, int x, int y, int color);
double	mod(double *v);
void	rgb_to_hex(int *rgb, int *hex);
void	*hex_to_rgb(int hex, int *rgb);
double	max(double a, double b);
double	cross_prod(double *u, double *v, int i);
double	dot_prod(double *u, double *v);
double	plane_dist(double *v, double *o, double *p);
double	segment_dist(double *A, double *B, double *p);
double	min(double a, double b);
double	dot2_prod(double *u);
double	dot_2d(double *u, double *v, int x, int y);
void	norm(double *u, double *v);

/*
**	init.c
*/

void	mouse_init(t_data *param);
void	vectors_init(t_data *param);
void	ft_init(t_data *param);

/*
**	cam_calc.c
*/

void	calculate_vectors(t_data *def);
void 	calculate_rotation(t_data *param);

/*
**	add_obj/
*/

t_sphere	**add_sp(t_sphere **sp, double *O, double r, int c);
t_plane		**add_pl(t_plane **pl, double *O, double *v, int c);
t_cylinder	**add_cy(t_cylinder **cy, double *O, double *v, double h, double d, int c);
t_light		**add_l(t_light **l, double *O, int c);
t_square	**add_sq(t_square **sq, double *O, double *v, double h, int c);
t_box		**add_bx(t_box **bx, double *O, double *v, double h, int c);
t_triangle	**add_tr(t_triangle **tr, double *A, double *B, double *C, int c);

/*
**	raymarching.c
*/

void	gen_ray(t_data *param, int x, int y, int boolean);
int		is_hit(t_data *param);
int		bounce_ray(t_data *param, int i);

/*
**	test_func.c
*/

void	show_camera(t_data *param);
void	show_pov(t_data *param);
void	show_obj(t_data *param);

/*
**	dist.c
*/

double	obj_dist(t_data *param);

/*
**	parse
*/

void set_settings(t_data *param, char *line);

#endif
