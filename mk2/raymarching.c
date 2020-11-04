/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:33:12 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	gen_ray(t_data *param, int x, int y, int boolean)
{
	int		i;

	i = -1;
	while (++i < 3)
		param->cam.ray.o[i] = param->cam.p[i] - (param->scr.x / 2 - x) *
			param->cam.vx[i] + (param->scr.y / 2 - y) * param->cam.vy[i];
	i = -1;
	while (++i < 3)
		param->cam.ray.v_o[i] = param->cam.ray.o[i] - param->cam.o[i];
	if (boolean)
		param->cam.ray.mod = mod(param->cam.ray.v_o);
	i = -1;
	while (++i < 3)
		param->cam.ray.v_o[i] /= param->cam.ray.mod;
}

int		bounce_ray(t_data *param, int i)
{
	double	dist;
	double	tray;
	int		j;

	j = -1;
	while (++j < 3)
	{
		param->cam.ray.o[j] = param->cam.ray.o_prev[j];
		param->cam.ray.v_l[j] = param->l[i]->o[j] - param->cam.ray.o[j];
	}
	param->cam.ray.mod = mod(param->cam.ray.v_l);
	j = -1;
	while (++j < 3)
		param->cam.ray.v_l[j] /= param->cam.ray.mod;
	dist = 2;
	tray = 0;
	while (dist > 0.001)
	{
		j = -1;
		while (++j < 3)
			param->cam.ray.o[j] += param->cam.ray.v_l[j] * dist;
		tray += dist;
		if (tray > param->cam.ray.mod)
		{
			j = -1;
			while (++j < 3)
				param->cam.ray.ray_rgb_l[j] += param->l[i]->rgb[j] /
										pow(param->cam.ray.mod / 2000, 2);
			return (1);
		}
		dist = obj_dist(param);
	}
	return (0);
}

int		is_hit(t_data *param)
{
	double	dist;
	double	tray;
	int		j;

	dist = 2;
	tray = 0;
	j = -1;
	while (++j < 3)
		param->cam.ray.ray_rgb_l[j] = 0;
	while (dist > 0.0001)
	{
		tray += dist;
		if (tray > 214747)
			return (0);
		j = -1;
		while (++j < 3)
			param->cam.ray.o[j] += param->cam.ray.v_o[j] * dist;
		dist = obj_dist(param);
	}
	hex_to_rgb(param->cam.ray.obj_c, param->cam.ray.ray_rgb_o);
	j = -1;
	while (++j < 3)
		param->cam.ray.o_prev[j] = param->cam.ray.o[j];
	return (1);
}
