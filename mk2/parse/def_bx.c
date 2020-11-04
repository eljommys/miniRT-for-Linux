/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_bx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:37:26 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 23:54:08 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_bx(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
	double	h;
	int		rgb[3];
	int		c;
	int		error;

	i = 2;
	error = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, P);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, v);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c);
	param->bx = add_bx(param->bx, P, v, h, c);
	if (error)
		return(1);
	return (0);
}
