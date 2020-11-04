/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:49:25 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 13:47:34 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	calculate_vectors(t_data *param)
{
	double	module;
	int		i;

	param->cam.Vx[0] = -param->cam.Vn[1];
	param->cam.Vx[1] = param->cam.Vn[0];
	param->cam.Vx[2] = 0;
	param->cam.Vy[0] = -param->cam.Vn[0] * param->cam.Vn[2];
	param->cam.Vy[1] = -param->cam.Vn[1] * param->cam.Vn[2];
	param->cam.Vy[2] = pow(param->cam.Vn[1], 2) + pow(param->cam.Vn[0], 2);
	i = -1;
	while (++i < 3)
		param->cam.P[i] = param->cam.O[i] + param->cam.Vn[i] * param->scr.dist;
	module = sqrt(pow(param->cam.Vx[0], 2) + pow(param->cam.Vx[1], 2));
	i = -1;
	while (++i < 2)
		param->cam.Vx[i] /= module;
	i = -1;
	while (++i < 3)
		param->cam.Vy[i] /= module;
}

void	copy_cam(t_data *param)
{
	int	j;

	j = -1;
	while (++j < 3)
	{
		param->c[param->cam.i]->O[j] = param->cam.O[j];
		param->c[param->cam.i]->v[j] = param->cam.Vn[j];
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
	param->cam.Vn[0] = cos(rotation_z_axis) * xy_projection;
	param->cam.Vn[1] = sin(rotation_z_axis) * xy_projection;
	param->cam.Vn[2] = sin(rotation_y_axis);
}
