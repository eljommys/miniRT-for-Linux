/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 10:57:57 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:10:03 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

double	sp_dist(t_data *param)
{
	double	dist;
	double	aux;
	int		i;

	dist = 2147483647;
	i = 0;
	while (param->sp[i])
	{
		aux = sqrt(pow(param->sp[i]->o[0] - param->cam.ray.o[0], 2) +
					pow(param->sp[i]->o[1] - param->cam.ray.o[1], 2) +
					pow(param->sp[i]->o[2] - param->cam.ray.o[2], 2)) -
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
