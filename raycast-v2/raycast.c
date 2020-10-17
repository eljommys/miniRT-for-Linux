/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 09:38:55 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/15 16:56:57 by jserrano         ###   ########.fr       */
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
		i++;
	}
}

void	calculate_rotation(t_data *param)
{
	double rotation_z_axis;
	double rotation_y_axis;

	rotation_z_axis = param->coord.x * 2 * param->mouse.speed * M_PI / 250 +
						param->rot.z;
	rotation_y_axis = param->coord.y * 2 * param->mouse.speed * M_PI / 250 +
						param->rot.y;
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

void	calculate_pixel(t_data *param, int *pixel, int i)
{
	if (param->p_conv[i][0] > param->screen.dist)
	{
		pixel[0] =  param->screen.x / 2 - (param->screen.dist *
					param->p_conv[i][1] / param->p_conv[i][0]);
		pixel[1] =  param->screen.y / 2 - (param->screen.dist *
					param->p_conv[i][2] / param->p_conv[i][0]);
	}
}

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
		j = -1;
		if (i < len)
			while (++j < 3)
				aux[i][j] = p[i][j];
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (p[i])
			free(p[i++]);
	free(p);
	return (aux);
}

/*
**	Cada cara son tres direcciones de memoria correspondientes a los puntos
**	convertidos (con la rotacion aplicada). Esto es asi para no tener que
**	hacer una funcion que busque que direcciones de la memoria son los puntos.
*/

double	***add_faces(double ***f, int n)
{
	double	***aux;
	int		len;
	int		i;
	int		j;

	len = 0;
	while (f[len])
		len++;
	if (!(aux = (double ***)malloc(sizeof(double **) * (len + n + 1))))
		return (f);
	i = -1;
	while(++i < len + n)
	{
		aux[i] = (double **)malloc(sizeof(double*) * 3);
		j = -1;
		if (i < len)
			while (++j < 3)
				aux[i][j] = f[i][j];
	}
	aux[i] = 0;
	i = 0;
	if (len)
		while (f[i])
			free(f[i++]);
	free(f);
	return (aux);
}

void	cube_faces(char *str, int n, t_data *param, int k, int pos)
{
	int f[3];
	int i;
	int j;

	f[0] = str[0] - 48;
	f[1] = str[1] - 48;
	f[2] = str[2] - 48;
	j = 0;
	i = -1;
	while (++i < 3)
	{
		param->faces[k][0] = param->p_conv[n + pos];
		param->faces[k][1] = param->p_conv[f[j] + pos];
		j++;
		if (j == 3)
			j = 0;
		param->faces[k][2] = param->p_conv[f[j] + pos];
		k++;
	}
}

void	create_cube(t_data *param, double *p, double h)
{
	int i;
	int j;
	int k;
	int pos;
	int f[3];

	i = 0;
	while (param->p[i])
		i++;
	k = 0;
	while (param->faces[k])
		k++;
	param->p = add_points(param->p, 8);
	param->p_conv = add_points(param->p_conv, 8);
	param->faces = add_faces(param->faces, 12);
	f[2] = -1;
	pos = i;
	while (++f[2] < 2)
	{
		f[1] = -1;
		while (++f[1] < 2)
		{
			f[0] = -1;
			while (++f[0] < 2)
			{
				j = -1;
				while (++j < 3)
					param->p[i][j] = p[j] + h * f[j];
				i++;
			}
		}
	}
	cube_faces("124", 0, param, k, pos);
	cube_faces("217", 3, param, k, pos);
	cube_faces("147", 5, param, k, pos);
	cube_faces("427", 6, param, k, pos);
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
	int i;
	int x;
	int y;

	y = -1;
	while (++y < param->screen.y)
	{
		x = -1;
		while (++x < param->screen.x)
			my_mlx_pixel_put(param, x, y, 0);
	}
	i = 0;
	while (param->p_conv[i])
	{
		calculate_pixel(param, pixel, i);
		i++;
	}
	mlx_put_image_to_window(param->id, param->win_id, param->img, 0, 0);
}
