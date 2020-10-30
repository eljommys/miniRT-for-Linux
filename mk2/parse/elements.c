/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:04:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 17:29:20 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static void	def_cam(t_data *param, char *line, int *i)
{
	double	P[3];
	double	v[3];
	int		fov;

	*i = 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_P(line, i, P);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_P(line, i, v);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	fov = ft_atoi(line + *i);
	while ('0' <= line[*i] && line[*i] <= '9')
		(*i)++;
	//implementar varias camaras
}

static void		def_light(t_data *param, char *line, int *i)
{
	int		j;
	double	P[3];
	double	alpha;
	int		rgb[3];
	int		c;

	*i = 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_P(line, i, P);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_d(line, i, &alpha);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_rgb(line, i, rgb);
	j = -1;
	while (++j < 3)
		rgb[j] *= alpha;
	rgb_to_hex(rgb, &c);
	param->l = add_l(param->l, P, c);
}

void		def_elm(t_data *param, char *line)
{
	int		i;

	i = 0;
	/*if (line[i] == 'c')
		def_cam(param, line, &i);
	else */if (line[i] == 'l')
		def_light(param, line, &i);
}
