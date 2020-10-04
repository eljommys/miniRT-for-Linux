/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/04 18:30:31 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/*
**	El plano de camara tiene un origen "P" que es el centro.
**	A partir de él nacen los ejes en forma de vectores unitarios "Vx" y "Vy".
**	Para calcular cualquier punto del plano en el espacio solo
**	basta con hacer la siguiente operacion:
**			P' = P + (x - (res_X / 2) * Vx) + (y - (res_Y / 2) * Vy)
**	donde "x" es la coordenada dentro de la pantalla correspondiente
**	al eje horizontal que va desde 0 hasta la resolucion
**	(1920 o 600 por defecto)
**	e "y" es la coordenada dentro de la pantalla correspondiente al
**	eje vertical que va desde 0 hasta la resolucion (1080 o 600 por defecto).
*/

void	calculate_vectors(t_data *param)
{
	double module;
	int		i;

	param->Vx[0] = -param->Vn[1];
	param->Vx[1] = param->Vn[0];
	param->Vx[2] = 0;
	param->Vy[0] = -param->Vn[0] * param->Vn[2];
	param->Vy[1] = -param->Vn[1] * param->Vn[2];
	param->Vy[2] = pow(param->Vn[1], 2) + pow(param->Vn[0], 2);
	i = -1;
	while (++i < 3)
		param->P[i] = param->O[i] + param->Vn[i] * param->screen_dist;
	module = sqrt(pow(param->Vx[0], 2) + pow(param->Vx[1], 2));
	i = -1;
	while (++i < 2)
		param->Vx[i] /= module;
	i = -1;
	while (++i < 3)
		param->Vy[i] /= module;
}

static void	my_mlx_pixel_put(t_data *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * param->line_length + x *
			(param->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	calculate_rotation(t_data *param)
{
	double rotation_z_axis;
	double rotation_y_axis;
	double xy_projection;

	rotation_z_axis = param->x * 2 * M_PI / 250 + param->rotation_z_axis;
	rotation_y_axis = param->y * M_PI / 500;
	xy_projection = cos(rotation_y_axis);
	param->Vn[0] = cos(rotation_z_axis) * xy_projection;
	param->Vn[1] = sin(rotation_z_axis) * xy_projection;
	param->Vn[2] = sin(rotation_y_axis);
}

void	gen_ray(t_data *param, int x, int y)
{
	int		i;
	double	module;

	i = -1;
	while (++i < 3)
		param->pixel[i] = param->P[i] - ((param->resolution_x / 2 + x) * param->Vx[i]) + ((param->resolution_y / 2 - y) * param->Vy[i]);
	i = -1;
	while (++i < 3)
		param->ray[i] = param->pixel[i] - param->O[i];
	module = sqrt(pow(param->ray[0], 2) + pow(param->ray[1], 2) + pow(param->ray[2], 2));
	i = -1;
	while (++i < 3)
		param->ray[i] /= module;
}


/*
** ****************************************************************************
** *************************FUNCIONES DE PRUEBA********************************
** ****************************************************************************
*/

/*
** Funcion de refresco de imagen
*/

void	show_camera(t_data *param)
{
	int x;
	int y;

	int O_planta[2];
	int O_alzado[2];
	int O_perfil[2];

	int up_left[3];
	int up_right[3];
	int down_left[3];
	int down_right[3];

	O_planta[0] = param->resolution_x / 4;
	O_planta[1] = (param->resolution_y / 4) * 3;

	O_alzado[0] = param->resolution_x / 4;
	O_alzado[1] = param->resolution_y / 4;

	O_perfil[0] = (param->resolution_x / 4) * 3;
	O_perfil[1] = param->resolution_y / 4;

	up_left[0] = param->P[0] - 50 * param->Vx[0] + 25 * param->Vy[0];
	up_left[1] = param->P[1] - 50 * param->Vx[1] + 25 * param->Vy[1];
	up_left[2] = param->P[2] - 50 * param->Vx[2] + 25 * param->Vy[2];

	up_right[0] = param->P[0] + 50 * param->Vx[0] + 25 * param->Vy[0];
	up_right[1] = param->P[1] + 50 * param->Vx[1] + 25 * param->Vy[1];
	up_right[2] = param->P[2] + 50 * param->Vx[2] + 25 * param->Vy[2];

	down_left[0] = param->P[0] - 50 * param->Vx[0] - 25 * param->Vy[0];
	down_left[1] = param->P[1] - 50 * param->Vx[1] - 25 * param->Vy[1];
	down_left[2] = param->P[2] - 50 * param->Vx[2] - 25 * param->Vy[2];

	down_right[0] = param->P[0] + 50 * param->Vx[0] - 25 * param->Vy[0];
	down_right[1] = param->P[1] + 50 * param->Vx[1] - 25 * param->Vy[1];
	down_right[2] = param->P[2] + 50 * param->Vx[2] - 25 * param->Vy[2];

	y = 0;
	while (y < param->resolution_y)
	{
		x = 0;
		while (x < param->resolution_x)
		{
			if (x == param->resolution_x / 2 || y == param->resolution_y / 2)
				my_mlx_pixel_put(param, x, y, 0xFFFFFF);
			else if (param->button == 0)
				my_mlx_pixel_put(param, x, y, 0x000000);
			x++;
		}
		y++;
	}

	my_mlx_pixel_put(param, O_planta[0] + up_left[0],
					O_planta[1] + up_left[1], 0xFF0000);
	my_mlx_pixel_put(param, O_planta[0] + up_right[0],
					O_planta[1] + up_right[1], 0xFF0000);
	my_mlx_pixel_put(param, O_planta[0] + down_left[0],
					O_planta[1] + down_left[1], 0x4EC7FF);
	my_mlx_pixel_put(param, O_planta[0] + down_right[0],
					O_planta[1] + down_right[1], 0x4EC7FF);
	my_mlx_pixel_put(param, O_planta[0] + param->P[0],
					O_planta[1] + param->P[1], 0xFFFFFF);
	my_mlx_pixel_put(param, O_planta[0] + param->O[0],
					O_planta[1] + param->O[1], 0xFFFFFF);

	my_mlx_pixel_put(param, O_alzado[0] + up_left[0],
					O_alzado[1] - up_left[2], 0xFF0000);
	my_mlx_pixel_put(param, O_alzado[0] + up_right[0],
					O_alzado[1] - up_right[2], 0xFF0000);
	my_mlx_pixel_put(param, O_alzado[0] + down_left[0],
					O_alzado[1] - down_left[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_alzado[0] + down_right[0],
					O_alzado[1] - down_right[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_alzado[0] + param->P[0],
					O_alzado[1] - param->P[2], 0xFFFFFF);
	my_mlx_pixel_put(param, O_alzado[0] + param->O[0],
					O_alzado[1] - param->O[2], 0xFFFFFF);

	my_mlx_pixel_put(param, O_perfil[0] + up_left[1],
					O_perfil[1] - up_left[2], 0xFF0000);
	my_mlx_pixel_put(param, O_perfil[0] + up_right[1],
					O_perfil[1] - up_right[2], 0xFF0000);
	my_mlx_pixel_put(param, O_perfil[0] + down_left[1],
					O_perfil[1] - down_left[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_perfil[0] + down_right[1],
					O_perfil[1] - down_right[2], 0x4EC7FF);
	my_mlx_pixel_put(param, O_perfil[0] + param->P[1],
					O_perfil[1] - param->P[2], 0xFFFFFF);
	my_mlx_pixel_put(param, O_perfil[0] + param->O[1],
					O_perfil[1] - param->O[2], 0xFFFFFF);

	mlx_put_image_to_window(param->id, param->win_id, param->img, 0, 0);

}

void	show_pov(t_data *param)
{
	int x;
	int y;

	y = 0;
	while (y < param->resolution_y)
	{
		x = 0;
		while (x < param->resolution_x)
		{
			gen_ray(param, x, y);
			if (param->ray[1] >= 0 && param->ray[0] >= 0 || param->ray[1] < 0 && param->ray[0] < 0)
				my_mlx_pixel_put(param, x, y, 0xFFFFFF);
			else
				my_mlx_pixel_put(param, x, y, 0);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img, 0, 0);
}
