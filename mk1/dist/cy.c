/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:02:30 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/24 11:20:26 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

double	cy_dist(t_data *param)
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
		d_xy[1] = mod(dy_v);
		d_xy[0] = plane_dist(param->cy[ij[0]]->v, param->cy[ij[0]]->O,
				param->cam.ray.O);
		a_d[0] = sqrt(pow(max(d_xy[0] - param->cy[ij[0]]->h / 2, 0), 2) +
				pow(max(d_xy[1] - param->cy[ij[0]]->d / 2, 0), 2));
		param->cam.ray.obj_n = (a_d[0] < a_d[1]) ? ij[0] : param->cam.ray.obj_n;
		a_d[1] = (a_d[0] < a_d[1]) ? a_d[0] : a_d[1];
	}
	return (a_d[1]);
}
