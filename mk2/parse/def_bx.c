/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_bx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:37:26 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:56:58 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	bx_points(char *line, int *error, double **p_v, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, p_v[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, p_v[1]);
}

int			def_bx(t_data *param, char *line)
{
	int		i;
	double	*p_v[2];
	double	h;
	int		rgb[3];
	int		c_error[2];

	i = 2;
	c_error[1] = 0;
	p_v[0] = (double *)malloc(sizeof(double) * 3);
	p_v[1] = (double *)malloc(sizeof(double) * 3);
	bx_points(line, &c_error[1], p_v, &i);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c_error[0]);
	param->bx = add_bx(param->bx, p_v, h, c_error[0]);
	free(p_v[0]);
	free(p_v[1]);
	if (c_error[1])
		return (1);
	return (0);
}
