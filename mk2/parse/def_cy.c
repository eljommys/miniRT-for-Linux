/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:07:29 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 23:55:05 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_cy(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
	double	d;
	double	h;
	int		rgb[3];
	int		c;
	int		error;

	error = 0;
	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, P);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_P(line, &i, v);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_rgb(line, &i, rgb, 1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_d(line, &i, &d);
	rgb_to_hex(rgb, &c);
	param->cy = add_cy(param->cy, P, v, h, d, c);
	if (error)
		return (1);
	return (0);
}
