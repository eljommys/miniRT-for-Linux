/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_sq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:04:34 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 16:51:22 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_sq(t_data *param, char *line)
{
	int		i;
	double	*p_v[2];
	double	h;
	int		rgb[3];
	int		c;
	int		error;

	i = 2;
	error = 0;
	p_v[0] = (double *)malloc(sizeof(double) * 3);
	p_v[1] = (double *)malloc(sizeof(double) * 3);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, p_v[0]);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, p_v[1]);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c);
	param->sq = add_sq(param->sq, p_v, h, c);
	free(p_v[0]);
	free(p_v[1]);
	if (error)
		return (1);
	return (0);
}
