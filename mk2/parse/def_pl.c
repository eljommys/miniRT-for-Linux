/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:47:58 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 16:21:39 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

void		def_pl(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
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
	rgb_to_hex(rgb, &c);
	param->pl = add_pl(param->pl, P, v, c);
}
