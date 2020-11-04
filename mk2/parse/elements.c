/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:04:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 00:32:06 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	cam_points(char *line, int *i, double **p_v, int *error)
{
	*i = 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	*error += def_p(line, i, p_v[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	*error += def_p(line, i, p_v[1]);
}

static int	def_cam(t_data *param, char *line, int *i)
{
	double	*p_v[2];
	int		fov;
	int		error;

	p_v[0] = (double *)malloc(sizeof(double) * 3);
	p_v[1] = (double *)malloc(sizeof(double) * 3);
	error = 0;
	cam_points(line, i, p_v, &error);
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
	if (error)
		return (1);
	return (0);
}

static int	def_light(t_data *param, char *line, int *i)
{
	double	p[3];
	double	alpha;
	int		rgb[3];
	int		c_error[2];

	c_error[1] = 0;
	*i = 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	c_error[1] += def_p(line, i, p);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	c_error[1] += def_d(line, i, &alpha);
	if (alpha < 0 || alpha > 1)
		return (1);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	c_error[1] += def_rgb(line, i, rgb, alpha);
	rgb_to_hex(rgb, &c_error[0]);
	param->l = add_l(param->l, p, c_error[0]);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (c_error[1] || line[*i])
		return (1);
	return (0);
}

int			def_elm(t_data *param, char *line)
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
