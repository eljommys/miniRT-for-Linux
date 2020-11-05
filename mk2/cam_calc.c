/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:46:04 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 14:02:26 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	calculate_vectors(t_data *param)
{
	double	module;
	int		i;

	param->cam.vx[0] = -param->cam.vn[1];
	param->cam.vx[1] = param->cam.vn[0];
	param->cam.vx[2] = 0;
	param->cam.vy[0] = -param->cam.vn[0] * param->cam.vn[2];
	param->cam.vy[1] = -param->cam.vn[1] * param->cam.vn[2];
	param->cam.vy[2] = pow(param->cam.vn[1], 2) + pow(param->cam.vn[0], 2);
	i = -1;
	while (++i < 3)
		param->cam.p[i] = param->cam.o[i] + param->cam.vn[i] * param->scr.dist;
	module = sqrt(pow(param->cam.vx[0], 2) + pow(param->cam.vx[1], 2));
	i = -1;
	while (++i < 2)
		param->cam.vx[i] /= module;
	i = -1;
	while (++i < 3)
		param->cam.vy[i] /= module;
}

void	copy_cam(t_data *param)
{
	int	j;

	j = -1;
	while (++j < 3)
	{
		param->c[param->cam.i]->o[j] = param->cam.o[j];
		param->c[param->cam.i]->v[j] = param->cam.vn[j];
	}
}

void	calculate_rotation(t_data *param)
{
	double	rotation_z_axis;
	double	rotation_y_axis;
	double	xy_projection;

	rotation_z_axis = param->crd.x * 2 * param->mou.speed * M_PI / 250 +
						param->cam.rot_z;
	rotation_y_axis = param->crd.y * 2 * param->mou.speed * M_PI / 250 +
						param->cam.rot_y;
	xy_projection = cos(rotation_y_axis);
	param->cam.vn[0] = cos(rotation_z_axis) * xy_projection;
	param->cam.vn[1] = sin(rotation_z_axis) * xy_projection;
	param->cam.vn[2] = sin(rotation_y_axis);
}
