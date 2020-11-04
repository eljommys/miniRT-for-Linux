/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:38:01 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:06:35 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void		mouse_init(t_data *param)
{
	param->crd.x = 0;
	param->crd.y = 0;
	param->mou.x = 0;
	param->mou.y = 0;
	param->mou.speed = 0.25;
}

void		pos_init(t_data *param, int i)
{
	param->cam.o[0] = param->c[i]->o[0];
	param->cam.o[1] = param->c[i]->o[1];
	param->cam.o[2] = param->c[i]->o[2];
}

void		vectors_init(t_data *param, int j)
{
	int		i;

	i = -1;
	while (++i < 3)
		param->cam.vn[i] = param->c[j]->v[i];
	if (param->cam.vn[0] >= 0 && param->cam.vn[1] >= 0)
		param->cam.rot_z = asin(param->cam.vn[1]);
	else if (param->cam.vn[0] < 0 && param->cam.vn[1] >= 0)
		param->cam.rot_z = M_PI - asin(param->cam.vn[1]);
	else if (param->cam.vn[0] < 0 && param->cam.vn[1] < 0)
		param->cam.rot_z = M_PI + asin(param->cam.vn[1]);
	else if (param->cam.vn[0] >= 0 && param->cam.vn[1] < 0)
		param->cam.rot_z = 2 * M_PI - asin(param->cam.vn[1]);
	param->cam.rot_y = (param->cam.vn[2] >= 0) ? asin(param->cam.vn[2]) :
			2 * M_PI - asin(param->cam.vn[2]);
	param->scr.fov = param->c[j]->fov;
	param->scr.dist = (param->scr.x / 2) /
						tan((param->scr.fov / 2) * M_PI / 180);
}
