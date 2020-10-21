/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:30:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/21 11:25:21 by jserrano         ###   ########.fr       */
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
				param->pl[i]->v[2] * param->pl[i]->O[2]));
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
		i++;
	}
	return (dist);
}

static double	cy_dist(t_data *param) // me hace un prisma infinito. hacer una funcion que sea "double cross_prod(double *u, double *v, int i)" y devuelva el valor i de w
{
	double	dy_v[3];
	double	dy;
	double	dx;
	double	aux;
	double	dist;
	int		i;
	int		j;

	dist = 2147483647;
	i = 0;
	while (param->cy[i])
	{
		dy_v[0] =	(param->cam.ray.O[1] - param->cy[i]->O[1]) * param->cy[i]->v[0] -
					(param->cam.ray.O[2] - param->cy[i]->O[1]) * param->cy[i]->v[1];
		dy_v[1] =	(param->cam.ray.O[2] - param->cy[i]->O[2]) * param->cy[i]->v[0] -
					(param->cam.ray.O[0] - param->cy[i]->O[0]) * param->cy[i]->v[2];
		dy_v[2] =	(param->cam.ray.O[0] - param->cy[i]->O[0]) * param->cy[i]->v[1] -
					(param->cam.ray.O[1] - param->cy[i]->O[1]) * param->cy[i]->v[0];
		dy = 	mod(dy_v) / mod(param->cy[i]->v);
		dx =	fabs(param->cy[i]->v[0] * param->cam.ray.O[0] +
				param->cy[i]->v[1] * param->cam.ray.O[1] +
				param->cy[i]->v[2] * param->cam.ray.O[2] -
				(param->cy[i]->v[0] * param->cy[i]->O[0] +
				param->cy[i]->v[1] * param->cy[i]->O[1] +
				param->cy[i]->v[2] * param->cy[i]->O[2]));
		aux = sqrt(pow(max(dx - param->cy[i]->h / 2, 0), 2) +
				pow(max(dy - param->cy[i]->d / 2, 0), 2));
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
		i++;
	}
	return (dist);
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
	aux = cy_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->cy[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
	return (dist);
}
