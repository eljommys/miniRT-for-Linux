/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:29:54 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:42:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

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

static void		screen_init(t_data *param)
{
	param->win_id = mlx_new_window(param->id, param->scr.x,
								param->scr.y, "miniRT de jserrano");
	param->img.img = mlx_new_image(param->id, param->scr.x,
								param->scr.y);
	param->img.addr = mlx_get_data_addr(param->img.img,
	&param->img.bits_per_pixel, &param->img.line_length, &param->img.endian);
}

void			ft_init(t_data *param, char **argv)
{
	param->id = mlx_init();
	mlx_get_screen_size(param->id, &param->max_res[0], &param->max_res[1]);
	objs_init(param);
	parse(param, argv);
	screen_init(param);
	mouse_init(param);
	pos_init(param, 0);
	vectors_init(param, 0);
	calculate_rotation(param);
	calculate_vectors(param);
}
