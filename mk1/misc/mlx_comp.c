/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_comp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:57:37 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 12:58:16 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

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
