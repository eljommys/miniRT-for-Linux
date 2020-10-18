/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/17 23:46:08 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	gen_ray(t_data *param, int x, int y, int boolean)
{
	int		i;

	i = -1;
	while (++i < 3)
		param->cam.ray.O[i] = param->cam.P[i] - (param->scr.x / 2 - x) *
			param->cam.Vx[i] + (param->scr.y / 2 - y) * param->cam.Vy[i];
	i = -1;
	while (++i < 3)
		param->cam.ray.V[i] = param->cam.ray.O[i] - param->cam.O[i];
	if (boolean)
		param->cam.ray.mod = sqrt(pow(param->cam.ray.V[0], 2) +
					pow(param->cam.ray.V[1], 2) + pow(param->cam.ray.V[2], 2));
	i = -1;
	while (++i < 3)
		param->cam.ray.V[i] /= param->cam.ray.mod;
}

double	sp_dist(t_data *param)
{
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = 0;
	while (param->sp[i])
	{
		aux = sqrt(pow(param->sp[i]->O[0] - param->cam.ray.O[0], 2) +
					pow(param->sp[i]->O[1] - param->cam.ray.O[1], 2) +
					pow(param->sp[i]->O[2] - param->cam.ray.O[2], 2)) -
					param->sp[i]->r;
		if (aux < dist)
		{
			param->cam.ray.obj_c = param->sp[i]->col;
			dist = aux;
		}
		i++;
	}
	return (dist);
}

int		bounce_ray(t_data *param)
{
	double	dist;
	double	tray;
	int		j;

	j = -1;
	while (++j < 3)
		param->cam.ray.V[j] = param->l[0]->O[j] - param->cam.ray.O[j];
	param->cam.ray.mod = sqrt(pow(param->cam.ray.V[0], 2) +
				pow(param->cam.ray.V[1], 2) + pow(param->cam.ray.V[2], 2));
	j = -1;
	while (++j < 3)
		param->cam.ray.V[j] /= param->cam.ray.mod;
	dist = 2;
	tray = 0;
	while (dist > 0.001)
	{
		j = -1;
		while (++j < 3)
			param->cam.ray.O[j] += param->cam.ray.V[j] * dist;
		tray += dist;
		if (tray > param->cam.ray.mod)
			return (1);
		dist = sp_dist(param);
	}
	param->cam.ray.ray_c = 0x2B2B2B;
	return (0);
}

int		is_hit(t_data *param)
{
	double dist;
	double tray;
	int		j;

	dist = 2;
	tray = 0;
	while (dist > 0.001)
	{
		tray += dist;
		if (tray > 20000)
			return (0);
		j = -1;
		while (++j < 3)
			param->cam.ray.O[j] += param->cam.ray.V[j] * dist;
		dist = sp_dist(param);
	}
	param->cam.ray.ray_c = param->cam.ray.obj_c;
	return (1);
}
