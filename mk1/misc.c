/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:34:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/18 16:43:35 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

int ft_loop(t_data *param)
{
	show_sp(param);
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
	*hex = rgb[0] * 65536 + rgb[1] * 256 + rgb[2];
}

void	*hex_to_rgb(int hex, int *rgb)
{
	int i;

	i = 3;
	while (--i >= 0)
	{
		rgb[i] = hex % 256;
		//rgb[i] = (rgb[i] < 1) ? 0 : rgb[i];
		hex /= 256;
	}
}
