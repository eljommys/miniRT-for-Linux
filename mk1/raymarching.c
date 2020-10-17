/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/17 13:51:53 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	gen_ray(t_data *param, int x, int y, int boolean)
{
	int		i;

	i = -1;
	while (++i < 3)
		param->cam.pixel[i] = param->cam.P[i] - (param->scr.x / 2 - x) *
			param->cam.Vx[i] + (param->scr.y / 2 - y) * param->cam.Vy[i];
	i = -1;
	while (++i < 3)
		param->cam.ray[i] = param->cam.pixel[i] - param->cam.O[i];
	if (boolean)
		param->cam.ray_module = sqrt(pow(param->cam.ray[0], 2) +
					pow(param->cam.ray[1], 2) + pow(param->cam.ray[2], 2));
	i = -1;
	while (++i < 3)
		param->cam.ray[i] /= param->cam.ray_module;
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
		aux = sqrt(pow(param->sp[i]->O[0] - param->cam.pixel[0], 2) +
					pow(param->sp[i]->O[1] - param->cam.pixel[1], 2) +
					pow(param->sp[i]->O[2] - param->cam.pixel[2], 2)) -
					param->sp[0]->r;
		dist = (aux < dist) ? aux : dist;
		i++;
	}
	return (dist);
}

int		is_hit(t_data *param)
{
	double dist;
	double tray;
	int		j;

	dist = 10;
	tray = 0;
	while (dist > 5)
	{
		dist = sp_dist(param);
		tray += dist;
		if (tray > 20000)
			return (0);
		j = -1;
		while (++j < 3)
			param->cam.pixel[j] += param->cam.ray[j] * dist;
	}
	return (1);
}

