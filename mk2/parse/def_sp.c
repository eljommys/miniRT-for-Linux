/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:33:04 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 23:56:45 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_sp(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	d;
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
	error += def_d(line, &i, &d);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	error += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c);
	param->sp = add_sp(param->sp, P, d / 2, c);
	if (error)
		return (1);
	return (0);
}
