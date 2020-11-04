/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:07:29 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 00:05:49 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	cy_points(char *line, int *i_c_error, double **p_v)
{
	while (line[i_c_error[0]] == ' ' || line[i_c_error[0]] == '\t')
		i_c_error[0]++;
	i_c_error[2] += def_p(line, &i_c_error[0], p_v[0]);
	while (line[i_c_error[0]] == ' ' || line[i_c_error[0]] == '\t')
		i_c_error[0]++;
	i_c_error[2] += def_p(line, &i_c_error[0], p_v[1]);
}

int		def_cy(t_data *param, char *line)
{
	double	*p_v[2];
	double	d_h[2];
	int		rgb[3];
	int		i_c_error[3];

	i_c_error[0] = 2;
	i_c_error[2] = 0;
	p_v[0] = (double *)malloc(sizeof(double) * 2);
	p_v[1] = (double *)malloc(sizeof(double) * 2);
	cy_points(line, i_c_error, p_v);
	while (line[i_c_error[0]] == ' ' || line[i_c_error[0]] == '\t')
		i_c_error[0]++;
	i_c_error[2] += def_rgb(line, &i_c_error[0], rgb, 1);
	while (line[i_c_error[0]] == ' ' || line[i_c_error[0]] == '\t')
		i_c_error[0]++;
	i_c_error[2] += def_d(line, &i_c_error[0], &d_h[0]);
	while (line[i_c_error[0]] == ' ' || line[i_c_error[0]] == '\t')
		i_c_error[0]++;
	i_c_error[2] += def_d(line, &i_c_error[0], &d_h[1]);
	rgb_to_hex(rgb, &i_c_error[1]);
	param->cy = add_cy(param->cy, p_v, d_h, i_c_error[1]);
	free(p_v[0]);
	free(p_v[1]);
	if (i_c_error[2])
		return (1);
	return (0);
}
