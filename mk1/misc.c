/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:34:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/21 21:48:36 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

int ft_loop(t_data *param)
{
	show_obj(param);
	//show_pov(param);
	//show_camera(param);
	return (0);
}

int		ft_exit(t_data *param)
{
	free(param);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *param, int x, int y, int color)
{
	char	*dst;

	dst = param->img.addr + (y * param->img.line_length + x *
			(param->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	mod(double *v)
{
	return (sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2)));
}

void	rgb_to_hex(int *rgb, int *hex)
{
	int i;

	i = -1;
	while (++i < 3)
		rgb[i] = (rgb[i] > 255) ? 255 : rgb[i];
	*hex = rgb[0] * 65536 + rgb[1] * 256 + rgb[2];
}

void	*hex_to_rgb(int hex, int *rgb)
{
	int i;

	i = 3;
	while (--i >= 0)
	{
		rgb[i] = hex % 256;
		hex /= 256;
	}
}

double	max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

double	cross_prod(double *u, double *v, int i)
{
	if (i == 0)
		return (u[1] * v[2] - u[2] * v[1]);
	else if (i == 1)
		return (u[2] * v[0] - u[0] * v[2]);
	else if (i == 2)
		return (u[0] * v[1] - u[1] * v[0]);
	else
		return (0);
}

double	plane_dist(double *v, double *o, double *p)
{
	return (fabs(v[0] * p[0] + v[1] * p[1] + v[2] * p[2] -
				(v[0] * o[0] + v[1] * o[1] + v[2] * o[2])));
}
