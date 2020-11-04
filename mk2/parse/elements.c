/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:04:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 23:59:31 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static int	def_cam(t_data *param, char *line, int *i)
{
	double	*p_v[2];
	int		fov;
	int		error;

	p_v[0] = (double *)malloc(sizeof(double) * 3);
	p_v[1] = (double *)malloc(sizeof(double) * 3);
	error = 0;
	*i = 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, p_v[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error +=def_p(line, i, p_v[1]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	fov = ft_atoi(line + *i);
	if (fov < 0 || fov > 179)
		return (1);
	while (ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i])
		return (1);
	param->c = add_c(param->c, p_v, fov);
	param->cam.n++;
	free(p_v[0]);
	free(p_v[1]);
	return (0);
}

static int	def_light(t_data *param, char *line, int *i)
{
	double	P[3];
	double	alpha;
	int		rgb[3];
	int		c;
	int		error;

	error = 0;
	*i = 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_p(line, i, P);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_d(line, i, &alpha);
	if (alpha < 0 || alpha > 1)
		return (1);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	error += def_rgb(line, i, rgb, alpha);
	rgb_to_hex(rgb, &c);
	param->l = add_l(param->l, P, c);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (error || line[*i])
		return (1);
	return (0);
}

int 		def_elm(t_data *param, char *line)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	if (!ft_memcmp(line, "c ", 2) || !ft_memcmp(line, "c\t", 2))
		error += def_cam(param, line, &i);
	else if (!ft_memcmp(line, "l ", 2) || !ft_memcmp(line, "l\t", 2))
		error += def_light(param, line, &i);
	if (error)
		return (1);
	return (0);
}
