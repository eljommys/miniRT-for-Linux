/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:03:34 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/24 11:03:43 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

double	bx_dist(t_data *param)
{
	double	d_xyz[3];
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = -1;
	while (param->bx[++i])
	{
		d_xyz[2] =
			plane_dist(param->bx[i]->v, param->bx[i]->O, param->cam.ray.O);
		d_xyz[1] =
			plane_dist(param->bx[i]->y, param->bx[i]->O, param->cam.ray.O);
		d_xyz[0] =
			plane_dist(param->bx[i]->x, param->bx[i]->O, param->cam.ray.O);
		aux = sqrt(pow(max(d_xyz[2], 0), 2) +
		pow(max(d_xyz[0] - param->bx[i]->h / 2, 0), 2) +
		pow(max(d_xyz[1] - param->bx[i]->h / 2, 0), 2));
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
	}
	return (dist);
}
