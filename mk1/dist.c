/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:30:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/21 15:53:02 by jserrano         ###   ########.fr       */
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

static double	sq_dist(t_data *param)
{

}

static double	cy_dist(t_data *param)
{
	double	PX[3];
	double	dy_v[3];
	double	d_xy[2];
	double	a_d[2];
	int		ij[2];

	a_d[1] = 2147483647;
	ij[0] = -1;
	while (param->cy[++ij[0]])
	{
		ij[1] = -1;
		while (++ij[1] < 3)
			PX[ij[1]] = param->cam.ray.O[ij[1]] - param->cy[ij[0]]->O[ij[1]];
		ij[1] = -1;
		while (++ij[1] < 3)
			dy_v[ij[1]] = cross_prod(PX, param->cy[ij[0]]->v, ij[1]);
		d_xy[1] = 	mod(dy_v) / mod(param->cy[ij[0]]->v);
		d_xy[0] = fabs(param->cy[ij[0]]->v[0] * param->cam.ray.O[0] +
				param->cy[ij[0]]->v[1] * param->cam.ray.O[1] +
				param->cy[ij[0]]->v[2] * param->cam.ray.O[2] -
				(param->cy[ij[0]]->v[0] * param->cy[ij[0]]->O[0] +
				param->cy[ij[0]]->v[1] * param->cy[ij[0]]->O[1] +
				param->cy[ij[0]]->v[2] * param->cy[ij[0]]->O[2]));
		a_d[0] = sqrt(pow(max(d_xy[0] - param->cy[ij[0]]->h / 2, 0), 2) +
				pow(max(d_xy[1] - param->cy[ij[0]]->d / 2, 0), 2));
		param->cam.ray.obj_n = (a_d[0] < a_d[1]) ? ij[0] : param->cam.ray.obj_n;
		a_d[1] = (a_d[0] < a_d[1]) ? a_d[0] : a_d[1];
	}
	return (a_d[1]);
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
