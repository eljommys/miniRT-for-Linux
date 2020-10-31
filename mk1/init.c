/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:38:01 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/31 12:27:45 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void		mouse_init(t_data *param)
{
	param->crd.x = 0;
	param->crd.y = 0;
	param->mou.x = 0;
	param->mou.y = 0;
	param->mou.speed = 0.25;
}

static void		screen_init(t_data *param)
{
	param->scr.x = 1240;
	param->scr.y = 720;
	param->id = mlx_init();
	param->win_id = mlx_new_window(param->id, param->scr.x,
								param->scr.y, "hola");
	param->img.img = mlx_new_image(param->id, param->scr.x,
								param->scr.y);
	param->img.addr = mlx_get_data_addr(param->img.img,
	&param->img.bits_per_pixel, &param->img.line_length, &param->img.endian);
}

void		pos_init(t_data *param)
{
	param->cam.O[0] = 0;
	param->cam.O[1] = 0;
	param->cam.O[2] = 0;
}

void		vectors_init(t_data *param)
{
	int		i;
	double	module;

	param->cam.Vn[0] = 1;
	param->cam.Vn[1] = 0;
	param->cam.Vn[2] = 0;
	module = mod(param->cam.Vn);
	i = -1;
	while (++i < 3)
		param->cam.Vn[i] /= module;
	if (param->cam.Vn[0] >= 0 && param->cam.Vn[1] >= 0)
		param->cam.rot_z = asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] < 0 && param->cam.Vn[1] >= 0)
		param->cam.rot_z = M_PI - asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] < 0 && param->cam.Vn[1] < 0)
		param->cam.rot_z = M_PI + asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] >= 0 && param->cam.Vn[1] < 0)
		param->cam.rot_z = 2 * M_PI - asin(param->cam.Vn[1]);
	param->cam.rot_y = (param->cam.Vn[2] >= 0) ? asin(param->cam.Vn[2]) :
			2 * M_PI - asin(param->cam.Vn[2]);
	param->scr.fov = 90;
	param->scr.dist = (param->scr.x / 2) /
						tan((param->scr.fov / 2) * M_PI / 180);
}

static void		objs_init(t_data *param)
{
	param->l = (t_light **)malloc(sizeof(t_light *));
	param->l[0] = 0;
	param->sp = (t_sphere **)malloc(sizeof(t_sphere *));
	param->sp[0] = 0;
	param->pl = (t_plane **)malloc(sizeof(t_plane *));
	param->pl[0] = 0;
	param->cy = (t_cylinder **)malloc(sizeof(t_cylinder *));
	param->cy[0] = 0;
	param->sq = (t_square **)malloc(sizeof(t_square *));
	param->sq[0] = 0;
	param->bx = (t_box **)malloc(sizeof(t_box *));
	param->bx[0] = 0;
	param->tr = (t_triangle **)malloc(sizeof(t_triangle *));
	param->tr[0] = 0;
}

void	ft_init(t_data *param)
{
	double p0[3];
	double p1[3];
	double p3[3];
	double l0[3];
	double l1[3];
	double v0[3];
	double v1[3];

	p0[0] = 1500;
	p0[1] = 1500;
	p0[2] = 0;

	p1[0] = 500;
	p1[1] = 500;
	p1[2] = 1;

	p3[0] = 3500;
	p3[1] = -3500;
	p3[2] = -1000;

	l0[0] = -500;
	l0[1] = -500;
	l0[2] = 1000;

	l1[0] = -500;
	l1[1] = 500;
	l1[2] = 1000;

	v0[0] = 0;
	v0[1] = 1;
	v0[2] = 1;

	v1[0] = 0;
	v1[1] = 0;
	v1[2] = 1;

	mouse_init(param);
	screen_init(param);
	pos_init(param);
	vectors_init(param);
	calculate_rotation(param);
	calculate_vectors(param);
	objs_init(param);
	param->cy = add_cy(param->cy, p1, v0, 200, 300, 0xdc8c2e);
	param->sp = add_sp(param->sp, p0, 500, 0xb15a76);
	param->sp = add_sp(param->sp, p3, 3000, 0x8abb76);
	param->sq = add_sq(param->sq, p1, v0, 500, 0xC2E680);
	param->pl = add_pl(param->pl, p3, v1, 0xD2C9C3);
	//param->tr = add_tr(param->tr, p0, p1, p3, 0xb15a76);
	param->l = add_l(param->l, l1, 0xe6c47c);
	param->l = add_l(param->l, l0, 0xb3c4bd);
	param->amb_l = 0x727cbd;
	hex_to_rgb(param->amb_l, param->amb_l_rgb);
}
