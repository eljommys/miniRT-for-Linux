/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 21:00:17 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 17:47:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

/*
**	var[3] = j, x, y
*/

static void	is_inside_ifs(t_data *param, int *var, int i)
{
	if (!param->tr[i]->nor[2])
	{
		if (!param->tr[i]->nor[1])
			var[1] = 1;
		else
			var[1] = 0;
		var[2] = 2;
	}
	else
	{
		var[1] = 0;
		var[2] = 1;
	}
}

static int	is_inside(t_data *param, int i)
{
	double	w[2];
	double	ac[3];
	double	ab[3];
	double	ap[3];
	int		var[3];

	is_inside_ifs(param, var, i);
	var[0] = -1;
	while (++var[0] < 3)
	{
		ab[var[0]] = param->tr[i]->ab[var[0]];
		ac[var[0]] = param->tr[i]->ac[var[0]];
		ap[var[0]] = param->cam.ray.O[var[0]] - param->tr[i]->A[var[0]];
	}
	w[1] = (dot_2d(ap, ac, var[1], var[2]) * dot_2d(ac, ab, var[1], var[2]) -
		dot_2d(ap, ab, var[1], var[2]) * dot_2d(ac, ac, var[1], var[2])) /
			(dot_2d(ab, ac, var[1], var[2]) * dot_2d(ac, ab, var[1], var[2]) -
			dot_2d(ab, ab, var[1], var[2]) * dot_2d(ac, ac, var[1], var[2]));
	w[0] = (dot_2d(ap, ac, var[1], var[2]) -
			w[1] * dot_2d(ab, ac, var[1], var[2])) /
			dot_2d(ac, ac, var[1], var[2]);
	if (w[0] >= 0 && w[0] < 1 && w[1] >= 0 && w[1] < 1 && w[0] + w[1] <= 1)
		return (1);
	return (0);
}

static double	contour_dist(t_data *param, int i)
{
	double	aux;
	double	dist;

	dist = segment_dist(param->tr[i]->A, param->tr[i]->B, param->cam.ray.O);
	aux = segment_dist(param->tr[i]->B, param->tr[i]->C, param->cam.ray.O);
	dist = (aux < dist) ? aux : dist;
	aux = segment_dist(param->tr[i]->C, param->tr[i]->A, param->cam.ray.O);
	dist = (aux < dist) ? aux : dist;
	return (dist);
}

double 		tr_dist(t_data *param)
{
	int i;
	double	aux;
	double	dist;

	i = -1;
	dist = 2147483647;
	while (param->tr[++i])
	{
		aux = (is_inside(param, i)) ?
			plane_dist(param->tr[i]->nor, param->tr[i]->A, param->cam.ray.O) :
			contour_dist(param, i);
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
	}
	return (dist);
}
