/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:23:47 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 13:23:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

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
