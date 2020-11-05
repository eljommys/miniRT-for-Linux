/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:45:20 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 17:22:41 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void	draw_pixel(t_data *param, int x, int y)
{
	int i;

	gen_ray(param, x, y, 1);
	param->cam.ray.ray_c = param->amb_l;
	if (is_hit(param))
	{
		i = -1;
		while (param->l[++i])
			bounce_ray(param, i);
		i = -1;
		while (++i < 3)
			param->cam.ray.ray_rgb[i] = (param->cam.ray.ray_rgb_o[i] *
			(double)param->cam.ray.ray_rgb_l[i] / 255) +
			(param->cam.ray.ray_rgb_o[i] * (double)param->amb_l_rgb[i] / 255);
		rgb_to_hex(param->cam.ray.ray_rgb, &param->cam.ray.ray_c);
	}
	my_mlx_pixel_put(param, x, y, param->cam.ray.ray_c);
}

int			show_obj(t_data *param)
{
	int x;
	int y;
	int step;

	step = (param->key == KEY_ENT) ? 1 : 8;
	y = -1;
	while (++y < param->scr.y)
	{
		x = -1;
		while (++x < param->scr.x)
		{
			if (!(x % step) && !(y % step))
				draw_pixel(param, x, y);
			else
				my_mlx_pixel_put(param, x, y, 0);
		}
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img.img, 0, 0);
	return (0);
}
