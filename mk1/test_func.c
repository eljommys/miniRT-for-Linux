/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:45:20 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/17 14:12:26 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	show_camera(t_data *param)
{
	int x;
	int y;

	int O_planta[2];
	int O_alzado[2];
	int O_perfil[2];

	int up_left[3];
	int up_right[3];
	int down_left[3];
	int down_right[3];

	O_planta[0] = param->scr.x / 4;
	O_planta[1] = (param->scr.y / 4) * 3;

	O_alzado[0] = param->scr.x / 4;
	O_alzado[1] = param->scr.y / 4;

	O_perfil[0] = (param->scr.x / 4) * 3;
	O_perfil[1] = param->scr.y / 4;

	up_left[0] = param->cam.P[0] - 50 * param->cam.Vx[0] + 25 * param->cam.Vy[0];
	up_left[1] = param->cam.P[1] - 50 * param->cam.Vx[1] + 25 * param->cam.Vy[1];
	up_left[2] = param->cam.P[2] - 50 * param->cam.Vx[2] + 25 * param->cam.Vy[2];

	up_right[0] = param->cam.P[0] + 50 * param->cam.Vx[0] + 25 * param->cam.Vy[0];
	up_right[1] = param->cam.P[1] + 50 * param->cam.Vx[1] + 25 * param->cam.Vy[1];
	up_right[2] = param->cam.P[2] + 50 * param->cam.Vx[2] + 25 * param->cam.Vy[2];

	down_left[0] = param->cam.P[0] - 50 * param->cam.Vx[0] - 25 * param->cam.Vy[0];
	down_left[1] = param->cam.P[1] - 50 * param->cam.Vx[1] - 25 * param->cam.Vy[1];
	down_left[2] = param->cam.P[2] - 50 * param->cam.Vx[2] - 25 * param->cam.Vy[2];

	down_right[0] = param->cam.P[0] + 50 * param->cam.Vx[0] - 25 * param->cam.Vy[0];
	down_right[1] = param->cam.P[1] + 50 * param->cam.Vx[1] - 25 * param->cam.Vy[1];
	down_right[2] = param->cam.P[2] + 50 * param->cam.Vx[2] - 25 * param->cam.Vy[2];

	y = 0;
	while (y < param->scr.y)
	{
		x = 0;
		while (x < param->scr.x)
		{
			if (x == param->scr.x / 2 || y == param->scr.y / 2)
				my_mlx_pixel_put(param, x, y, 0xFFFFFF);
			else
				my_mlx_pixel_put(param, x, y, 0x000000);
			x++;
		}
		y++;
	}

	my_mlx_pixel_put(param, O_planta[0] + up_left[0],
					O_planta[1] + up_left[1], 0xFF0000);
	my_mlx_pixel_put(param, O_planta[0] + up_right[0],
					O_planta[1] + up_right[1], 0xFF0000);
	my_mlx_pixel_put(param, O_planta[0] + down_left[0],
					O_planta[1] + down_left[1], 0x4EC7FF);
	my_mlx_pixel_put(param, O_planta[0] + down_right[0],
					O_planta[1] + down_right[1], 0x4EC7FF);
	my_mlx_pixel_put(param, O_planta[0] + param->cam.P[0],
					O_planta[1] + param->cam.P[1], 0xFFFFFF);
	my_mlx_pixel_put(param, O_planta[0] + param->cam.O[0],
					O_planta[1] + param->cam.O[1], 0xFFFFFF);

	my_mlx_pixel_put(param, O_alzado[0] + up_left[0],
					O_alzado[1] - up_left[2], 0xFF0000);
	my_mlx_pixel_put(param, O_alzado[0] + up_right[0],
					O_alzado[1] - up_right[2], 0xFF0000);
	my_mlx_pixel_put(param, O_alzado[0] + down_left[0],
					O_alzado[1] - down_left[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_alzado[0] + down_right[0],
					O_alzado[1] - down_right[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_alzado[0] + param->cam.P[0],
					O_alzado[1] - param->cam.P[2], 0xFFFFFF);
	my_mlx_pixel_put(param, O_alzado[0] + param->cam.O[0],
					O_alzado[1] - param->cam.O[2], 0xFFFFFF);

	my_mlx_pixel_put(param, O_perfil[0] + up_left[1],
					O_perfil[1] - up_left[2], 0xFF0000);
	my_mlx_pixel_put(param, O_perfil[0] + up_right[1],
					O_perfil[1] - up_right[2], 0xFF0000);
	my_mlx_pixel_put(param, O_perfil[0] + down_left[1],
					O_perfil[1] - down_left[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_perfil[0] + down_right[1],
					O_perfil[1] - down_right[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_perfil[0] + param->cam.P[1],
					O_perfil[1] - param->cam.P[2], 0xFFFFFF);
	my_mlx_pixel_put(param, O_perfil[0] + param->cam.O[1],
					O_perfil[1] - param->cam.O[2], 0xFFFFFF);

	mlx_put_image_to_window(param->id, param->win_id, param->img.img, 0, 0);

}

void	show_pov(t_data *param)
{
	int x;
	int y;

	y = 0;
	while (y < param->scr.y)
	{
		x = 0;
		while (x < param->scr.x)
		{
			gen_ray(param, x, y, 0);
			if (param->cam.ray[2] < 0)
			{
				if (param->cam.ray[1] < 0)
				{
					if (param->cam.ray[0] < 0)
						my_mlx_pixel_put(param, x, y, 0x864545);
					else
						my_mlx_pixel_put(param, x, y, 0x858645);
				}
				else
				{
					if (param->cam.ray[0] < 0)
						my_mlx_pixel_put(param, x, y, 0x458686);
					else
						my_mlx_pixel_put(param, x, y, 0x864581);
				}
			}
			else
			{
				if (param->cam.ray[1] < 0)
				{
					if (param->cam.ray[0] < 0)
						my_mlx_pixel_put(param, x, y, 0xFF5A5A);
					else
						my_mlx_pixel_put(param, x, y, 0xFFFF5A);
				}
				else
				{
					if (param->cam.ray[0] < 0)
						my_mlx_pixel_put(param, x, y, 0x5AFAFF);
					else
						my_mlx_pixel_put(param, x, y, 0xFF5AFF);
				}
			}
			x += 2;
		}
		y += 2;
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img.img, 0, 0);
}

void	show_sp(t_data *param)
{
	int x;
	int y;
	int i;
	int j;
	double dist;
	int color;

	y = 0;
	while (y <= param->scr.y / 2)
	{
		x = 0;
		while (x <= param->scr.x / 2)
		{
			i = -1;
			while (++i < 2)
			{
				j = -1;
				while (++j < 2)
				{
					if (!i && !j)
						gen_ray(param, x, y, 1);
					else
						gen_ray(param, j * (param->scr.x - x) + (1 - j) * x, i * (param->scr.y - y) + (1 - i) * y, 0);
					if (is_hit(param))
						my_mlx_pixel_put(param, j * (param->scr.x - x) + (1 - j) * x, i * (param->scr.y - y) + (1 - i) * y, 0xFFFFFF);
					else
						my_mlx_pixel_put(param, j * (param->scr.x - x) + (1 - j) * x, i * (param->scr.y - y) + (1 - i) * y, 0);
				}
			}
			x += 4;
		}
		y += 4;
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img.img, 0, 0);
}
