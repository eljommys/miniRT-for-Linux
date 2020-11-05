/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_sq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:04:34 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 00:13:25 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	sq_points(char *line, int *c_error, double **p_v, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	c_error[1] += def_p(line, i, p_v[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	c_error[1] += def_p(line, i, p_v[1]);
}

int			def_sq(t_data *param, char *line)
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
	sq_points(line, c_error, p_v, &i);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_d(line, &i, &h);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	c_error[1] += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c_error[0]);
	param->sq = add_sq(param->sq, p_v, h, c_error[0]);
	free(p_v[0]);
	free(p_v[1]);
	if (c_error[1])
		return (1);
	return (0);
}
