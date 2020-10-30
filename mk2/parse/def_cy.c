/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:07:29 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 16:20:50 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

void		def_cy(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
	double	d;
	double	h;
	int		rgb[3];
	int		c;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_P(line, &i, P);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_P(line, &i, v);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_rgb(line, &i, rgb);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_d(line, &i, &d);
	rgb_to_hex(rgb, &c);
	param->cy = add_cy(param->cy, P, v, h, d, c);
}
