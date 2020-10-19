/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:38:01 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/18 17:05:56 by jserrano         ###   ########.fr       */
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

void		vectors_init(t_data *param)
{
	int		i;
	double	module;

	param->cam.O[0] = 0;
	param->cam.O[1] = 0;
	param->cam.O[2] = 0;
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
	param->sp = (t_sphere **)malloc(sizeof(t_sphere *));
	param->sp[0] = 0;
	param->pl = (t_plane **)malloc(sizeof(t_plane *));
	param->pl[0] = 0;
	param->l = (t_light **)malloc(sizeof(t_light *));
	param->l[0] = 0;
}

void	ft_init(t_data *param)
{
	double p[3];
	double p1[3];
	double l0[3];
	double l1[3];
	double p3[3];
	double v[3];

	p[0] = 1500;
	p[1] = 1500;
	p[2] = 0;

	v[0] = 0;
	v[1] = 0;
	v[2] = 1;

	p1[0] = 500;
	p1[1] = 500;
	p1[2] = 0;

	l0[0] = -500;
	l0[1] = -500;
	l0[2] = 1000;

	l1[0] = -500;
	l1[1] = 500;
	l1[2] = 1000;

	p3[0] = 3500;
	p3[1] = -3500;
	p3[2] = -1000;

	mouse_init(param);
	screen_init(param);
	vectors_init(param);
	objs_init(param);
	param->sp = add_sp(param->sp, p1, 100, 0x0000FF);
	param->sp = add_sp(param->sp, p, 500, 0x00FF00);
	param->sp = add_sp(param->sp, p3, 3000, 0xFF0000);
	param->pl = add_pl(param->pl, p3, v, 0xFFFFFF);
	param->l = add_l(param->l, l1, 0xFF00FF);
	param->l = add_l(param->l, l0, 0xFFFF00);
}
