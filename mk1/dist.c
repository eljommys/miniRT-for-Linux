/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:30:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/24 13:16:02 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist/dist.h"

static double 	tr_dist(t_data *param)
{

}

double			obj_dist(t_data *param)
{
	double	dist;
	double	aux;

	dist = sp_dist(param);
	param->cam.ray.obj_c = (dist < 2147483647) ?
		param->sp[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	aux = pl_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->pl[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
	aux = cy_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->cy[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
	aux = sq_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->sq[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
	aux = bx_dist(param);
	param->cam.ray.obj_c = (aux < dist) ?
		param->bx[param->cam.ray.obj_n]->col : param->cam.ray.obj_c;
	dist = (aux < dist) ? aux : dist;
	return (dist);
}
