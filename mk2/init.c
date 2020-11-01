/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:38:01 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/01 22:09:40 by jserrano         ###   ########.fr       */
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
	param->id = mlx_init();
	param->win_id = mlx_new_window(param->id, param->scr.x,
								param->scr.y, "miniRT");
	param->img.img = mlx_new_image(param->id, param->scr.x,
								param->scr.y);
	param->img.addr = mlx_get_data_addr(param->img.img,
	&param->img.bits_per_pixel, &param->img.line_length, &param->img.endian);
}

void		pos_init(t_data *param, int i)
{
	param->cam.O[0] = param->c[i]->O[0];
	param->cam.O[1] = param->c[i]->O[1];
	param->cam.O[2] = param->c[i]->O[2];
}

void		vectors_init(t_data *param, int j)
{
	int		i;
	double	module;

	i = -1;
	while (++i < 3)
		param->cam.Vn[i] = param->c[j]->v[i];
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
	param->scr.fov = param->c[j]->fov;
	param->scr.dist = (param->scr.x / 2) /
						tan((param->scr.fov / 2) * M_PI / 180);
}

static void		objs_init(t_data *param)
{
	param->scr.x = -1;
	param->scr.y = -1;
	param->amb_l = -1;
	param->cam.n = 0;
	param->cam.i = 0;
	param->l = (t_light **)malloc(sizeof(t_light *));
	param->l[0] = 0;
	param->c = (t_cams **)malloc(sizeof(t_cams *));
	param->c[0] = 0;
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

void	ft_init(t_data *param, char **argv)
{
	objs_init(param);
	parse(param, argv);
	mouse_init(param);
	screen_init(param);
	pos_init(param, 0);
	vectors_init(param, 0);
	calculate_rotation(param);
	calculate_vectors(param);
}
