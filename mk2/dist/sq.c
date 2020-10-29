/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:01:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/24 11:01:42 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

double	sq_dist(t_data *param)
{
	double	d_xyz[3];
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = -1;
	while (param->sq[++i])
	{
		d_xyz[2] =
			plane_dist(param->sq[i]->v, param->sq[i]->O, param->cam.ray.O);
		d_xyz[1] =
			plane_dist(param->sq[i]->y, param->sq[i]->O, param->cam.ray.O);
		d_xyz[0] =
			plane_dist(param->sq[i]->x, param->sq[i]->O, param->cam.ray.O);
		aux = sqrt(pow(max(d_xyz[2], 0), 2) +
		pow(max(d_xyz[0] - param->sq[i]->h / 2, 0), 2) +
		pow(max(d_xyz[1] - param->sq[i]->h / 2, 0), 2));
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
	}
	return (dist);
}
