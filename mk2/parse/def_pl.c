/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:47:58 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 23:56:05 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

int		def_pl(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
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
	rgb_to_hex(rgb, &c);
	param->pl = add_pl(param->pl, P, v, c);
	if (error)
		return (1);
	return (0);
}
