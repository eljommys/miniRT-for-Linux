/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:18:02 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 01:49:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"
#include "def_ft.h"

static int def_res(t_data *param, char *line, int *i)
{
	int num_len;

	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] < '0' && '9' < line[*i])
		return (1);
	param->scr.x = (int)ft_atoi(line + *i);
	num_len = 0;
	while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
		num_len++;
	*i += num_len;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] < '0' && '9' < line[*i])
		return (1);
	param->scr.y = (int)ft_atoi(line + *i);
	num_len = 0;
	while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
		num_len++;
	*i += num_len;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i])
		return (1);
	return (0);
}

static int	def_amb(t_data *param, char *line, int *i)
{
	double	alpha;

	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (def_d(line, i, &alpha))
		return (1);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] < '0' && '9' < line[*i])
		return (1);
	if (def_rgb(line, i, param->amb_l_rgb, alpha))
		return (1);
	rgb_to_hex(param->amb_l_rgb, &(param->amb_l));
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i])
		return (1);
	return (0);
}

int		def_settings(t_data *param, char *line)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	if (line[i] == 'R')
	{
		if (param->scr.x == -1 && param->scr.y == -1)
			error += def_res(param, line, &i);
		else
			return (1);
	}
	else if (line[i] == 'A')
	{
		if (param->amb_l == -1)
			error += def_amb(param, line, &i);
		else
			return (1);
	}
	if (error)
		return (1);
	return (0);
}
