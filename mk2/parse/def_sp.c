/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:33:04 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 16:21:47 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

void		def_sp(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	d;
	int		rgb[3];
	int		c;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_P(line, &i, P);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_d(line, &i, &d);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_rgb(line, &i, rgb);
	rgb_to_hex(rgb, &c);
	param->sp = add_sp(param->sp, P, d / 2, c);
}
