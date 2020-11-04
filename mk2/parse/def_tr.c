/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_tr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:21:06 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 00:23:48 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	tr_points(char *line, double **abc, int *error, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, abc[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, abc[1]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, abc[2]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int			def_tr(t_data *param, char *line)
{
	int		i;
	double	*abc[3];
	int		rgb[3];
	int		c;
	int		error;

	i = 2;
	error = 0;
	abc[0] = (double *)malloc(sizeof(double) * 3);
	abc[1] = (double *)malloc(sizeof(double) * 3);
	abc[2] = (double *)malloc(sizeof(double) * 3);
	tr_points(line, abc, &error, &i);
	error += def_rgb(line, &i, rgb, 1);
	rgb_to_hex(rgb, &c);
	param->tr = add_tr(param->tr, abc, c);
	free(abc[0]);
	free(abc[1]);
	free(abc[2]);
	if (error)
		return (1);
	return (0);
}
