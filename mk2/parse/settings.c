/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:18:02 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 11:36:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void def_res(t_data *param, char *line, int *i)
{
	int num_len;

	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	param->scr.x = (int)ft_atoi(line + *i);
	num_len = 0;
	while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
		num_len++;
	*i += num_len;
	while (line[*i] != ' ' || line[*i] == '\t')
		(*i)++;
	param->scr.y = (int)ft_atoi(line + *i);
}

static void def_alpha(char *line, int *i, double *alpha)
{
	int	num_len;

	if (line[*i] == '1')
	{
		*alpha = 1;
		(*i)++;
	}
	else if (line[*i] == '0')
	{
		(*i)++;
		if (line[*i] == '.')
		{
			(*i)++;
			num_len = 0;
			while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
				num_len++;
			*alpha = (double)ft_atoi(line + *i) / pow(10, num_len);
			*i += num_len;
		}
		else
			*alpha = 0;
	}
}

static void	def_amb(t_data *param, char *line, int *i)
{
	int 	j;
	double	alpha;

	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	def_alpha(line, i, &alpha);
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	j = -1;
	while (++j < 3)
	{
		param->amb_l_rgb[j] = ft_atoi(line + *i) * alpha;
		while ('0' <= line[*i] && line[*i] <= '9')
			(*i)++;
		(*i)++;
	}
}

void		def_settings(t_data *param, char *line)
{
	int		i;
	double	alpha;

	i = 0;
	alpha = -1;
	if (line[i] == 'R')
		def_res(param, line, &i);
	else if (line[i] == 'A')
		def_amb(param, line, &i);
}
