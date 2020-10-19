/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/18 17:45:18 by jserrano         ###   ########.fr       */
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
		param->cam.ray.mod = mod(param->cam.ray.V);
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
			param->cam.ray.obj_n = i;
			dist = aux;
		}
		i++;
	}
	return (dist);
}

double	pl_dist(t_data *param)
{
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = 0;
	while (param->pl[i])
	{
		aux =	fabs(param->pl[i]->v[0] * param->cam.ray.O[0] +
				param->pl[i]->v[1] * param->cam.ray.O[1] +
				param->pl[i]->v[2] * param->cam.ray.O[2] -
				(param->pl[i]->v[0] * param->pl[i]->O[0] +
				param->pl[i]->v[1] * param->pl[i]->O[1] +
				param->pl[i]->v[2] * param->pl[i]->O[2])) /
				mod(param->pl[i]->v);
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
		i++;
	}
	return (dist);
}

double	obj_dist(t_data *param)
{
	double	dist;
	double	aux;

	dist = sp_dist(param);
	param->cam.ray.obj_c = param->sp[param->cam.ray.obj_n]->col;
	aux = pl_dist(param);
	param->cam.ray.obj_c = (aux < dist) ? param->pl[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
}

int		bounce_ray(t_data *param, int i)
{
	double	dist;
	double	tray;
	int		j;

	j = -1;
	while (++j < 3)
	{
		param->cam.ray.O[j] = param->cam.ray.O_prev[j];
		param->cam.ray.V[j] = param->l[i]->O[j] - param->cam.ray.O[j];
	}
	param->cam.ray.mod = mod(param->cam.ray.V);
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
		{
			j = -1;
			while (++j < 3)
				param->cam.ray.ray_rgb_l[j] += param->l[i]->rgb[j] / pow(param->cam.ray.mod / 2000, 2);
			return (1);
		}
		dist = obj_dist(param);
	}
	return (0);
}

int		is_hit(t_data *param)
{
	double dist;
	double tray;
	int		j;

	dist = 2;
	tray = 0;
	j = -1;
	while (++j < 3)
		param->cam.ray.ray_rgb_l[j] = 0;
	while (dist > 0.001)
	{
		tray += dist;
		if (tray > 2147483)
			return (0);
		j = -1;
		while (++j < 3)
			param->cam.ray.O[j] += param->cam.ray.V[j] * dist;
		dist = obj_dist(param);
	}
	hex_to_rgb(param->cam.ray.obj_c, param->cam.ray.ray_rgb_o);
	j = -1;
	while (++j < 3)
		param->cam.ray.O_prev[j] = param->cam.ray.O[j];
	return (1);
}
