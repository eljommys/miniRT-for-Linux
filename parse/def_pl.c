/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:47:58 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:59:13 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_pl(t_data *param, char *line)
{
	int		i;
	double	p[3];
	double	v[3];
	int		rgb[3];
	int		c_error[2];

	c_error[1] = 0;
	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_p(line, &i, p);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_p(line, &i, v);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c_error[0]);
	param->pl = add_pl(param->pl, p, v, c_error[0]);
	if (c_error[1])
		return (1);
	return (0);
}
