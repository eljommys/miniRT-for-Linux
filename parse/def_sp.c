/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:33:04 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:59:14 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_sp(t_data *param, char *line)
{
	int		i;
	double	p[3];
	double	d;
	int		rgb[3];
	int		c_error[2];

	i = 2;
	c_error[1] = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_p(line, &i, p);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_d(line, &i, &d);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c_error[0]);
	param->sp = add_sp(param->sp, p, d / 2, c_error[0]);
	if (c_error[1])
		return (1);
	return (0);
}
