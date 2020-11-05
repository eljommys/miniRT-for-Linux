/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 11:00:02 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:09:30 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

double	pl_dist(t_data *param)
{
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = 0;
	while (param->pl[i])
	{
		aux = plane_dist(param->pl[i]->v, param->pl[i]->o, param->cam.ray.o);
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
		i++;
	}
	return (dist);
}
