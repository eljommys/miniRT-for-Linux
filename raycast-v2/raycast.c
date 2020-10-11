/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/11 14:09:20 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	my_mlx_pixel_put(t_data *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * param->line_length + x *
			(param->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	point_rot(t_data *param)
{
	int i;

	i = 0;
	while (param->p[i])
	{
		param->p_conv[i][0] = (param->p[i][0] * param->rot.cos_z -
								param->p[i][1] * param->rot.sin_z) *
								param->rot.cos_y + param->p[i][2] *
								param->rot.sin_y + param->rot.Vd[0];
		param->p_conv[i][1] = param->p[i][0] * param->rot.sin_z +
								param->p[i][1] * param->rot.cos_z +
								param->rot.Vd[1];
		param->p_conv[i][2] = -(param->p[i][0] * param->rot.cos_z -
								param->p[i][1] * param->rot.sin_z) *
								param->rot.sin_y + param->p[i][2] *
								param->rot.cos_y + param->rot.Vd[2];
	}
}

void	calculate_rotation(t_data *param)
{
	double rotation_z_axis;
	double rotation_y_axis;

	rotation_z_axis = param->coord.x * 2 * param->mouse.speed * M_PI / 250 + param->rot.z;
	rotation_y_axis = param->coord.y * 2 * param->mouse.speed * M_PI / 250 + param->rot.y;
	param->rot.cos_y = cos(rotation_y_axis);
	param->rot.sin_y = sin(rotation_y_axis);
	param->rot.cos_z = cos(rotation_z_axis);
	param->rot.sin_z = sin(rotation_z_axis);
	param->Vn[0] = param->rot.cos_z * param->rot.cos_y;
	param->Vn[1] = param->rot.sin_z * param->rot.cos_y;
	param->Vn[2] = param->rot.sin_y;
	point_rot(param);
}

/*
**	falta filtrar solo los puntos que estan dentro del cono de vision
*/

void	calculate_pixel(t_data *param, int *pixel)
{
	int		i;

	i = 0;
	while (param->p[i])
	{
		if (param->p_conv[i][0] > param->screen.dist)
		{
			pixel[0] =  param->screen.x / 2 - (param->screen.dist * param->p_conv[i][1] / param->p_conv[i][0]);
			pixel[1] =  param->screen.y / 2 - (param->screen.dist * param->p_conv[i][2] / param->p_conv[i][0]);
		}
		if (0 < pixel[0] && pixel[0] < param->screen.x && 0 < pixel[1] && pixel[1] < param->screen.y)
			my_mlx_pixel_put(param, pixel[0], pixel[1], 0xFFFFFF);
	}
}

// reducir tamaño

double	**add_points(double **p, int n)
{
	double	**aux;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (p[len])
		len++;
	if (!(aux = (double **)malloc(sizeof(double *) * (len + n + 1))))
		return (p);
	i = -1;
	while(++i < len + n)
	{
		aux[i] = (double *)malloc(sizeof(double) * 3);
		if (i < len)
		{
			j = 0;
			while (j < 3)
				aux[i][j] = p[i][j++];
		}
	}
	aux[i] = 0;
	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
	return (aux);
}

void	create_cube(t_data *param, double *p1, double *p2)
{
	int i;
	int j;

	i = 0;
	while (param->p[i])
		i++;
	param->p = add_points(param->p, 8);
	param->p_conv = add_points(param->p_conv, 8);
	//definir estas variables bloquean todo el programa. tengo que ver como hacerlo mejor
	//	probablemente con la cadena de puntos en la estructura en lugar de una cadena de estructuras
	j = -1;
	while (++j < 3)
		param->p[i][j] = p1[j];

	param->p[i + 1][0] = p1[0];
	param->p[i + 1][1] = p2[1];
	param->p[i + 1][2] = p1[2];

	param->p[i + 2][0] = p2[0];
	param->p[i + 2][1] = p2[1];
	param->p[i + 2][2] = p1[2];

	param->p[i + 3][0] = p2[0];
	param->p[i + 3][1] = p1[1];
	param->p[i + 3][2] = p1[2];

	param->p[i + 4][0] = p1[0];
	param->p[i + 4][1] = p1[1];
	param->p[i + 4][2] = p2[2];

	param->p[i + 5][0] = p1[0];
	param->p[i + 5][1] = p2[1];
	param->p[i + 5][2] = p2[2];

	j = -1;
	while (++j < 3)
		param->p[i + 6][j] = p2[j];

	param->p[i + 7][0] = p2[0];
	param->p[i + 7][1] = p1[1];
	param->p[i + 7][2] = p2[2];
}

/*
** ****************************************************************************
** *************************FUNCIONES DE PRUEBA********************************
** ****************************************************************************
*/

/*
** Funcion de refresco de imagen
*/

void	show_pov(t_data *param)
{
	int pixel[2];
	int x;
	int y;

	calculate_pixel(param, pixel);
	y = -1;
	while (++y < param->screen.y)
	{
		x = -1;
		while (++x < param->screen.x)
			my_mlx_pixel_put(param, x, y, 0);
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img, 0, 0);
}
