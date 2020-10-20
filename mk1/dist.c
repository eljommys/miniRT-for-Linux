/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:30:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/20 15:52:48 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static double	sp_dist(t_data *param)
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

static double	pl_dist(t_data *param)
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

static double	cy_dist(t_data *param)
{
	double	axis[3];
	double	axis_d;
	int		i;

	i = 0;
	while (param->cy[i])
	{
		axis[0] = (param->cam.ray.O[0] - param->cy[i]->O[0] - pow(param->cy[i]->v[0], 2) * () //distancia de un punto a una recta

	}
}

double			obj_dist(t_data *param)
{
	double	dist;
	double	aux;

	dist = sp_dist(param);
	param->cam.ray.obj_c = param->sp[param->cam.ray.obj_n]->col;
	aux = pl_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->pl[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
}
