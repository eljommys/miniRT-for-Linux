/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:15:51 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 01:52:26 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def_ft.h"

int	def_P(char *line, int *i, double *P)
{
	int j;
	int num_len;

	if (!ft_isdigit(line[*i]) && line[*i] != '-')
		return (1);
	j = -1;
	while (++j < 3)
	{
		P[j] = (double)ft_atoi(line + *i);
		while (ft_isdigit(line[*i]) || line[*i] == '-')
			(*i)++;
		if (line[*i] != '.')
			return (1);
		(*i)++;
		num_len = 0;
		while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
			num_len++;
		P[j] += (double)ft_atoi(line + *i) / pow(10, num_len);
		*i += num_len;
		if (j < 2)
		{
			if (line[*i] != ',')
				return (1);
			(*i)++;
		}
	}
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] != ' ' && line[*i] != '\t' && line[*i])
		return (1);
	return (0);
}

int def_d(char *line, int *i, double *d)
{
	int num_len;

	if (!ft_isdigit(line[*i]))
		return (1);
	*d = (double)ft_atoi(line + *i);
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == '.' || line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	else
		return (1);
	num_len = 0;
	if (line[*i - 1] == '.')
	{
		while (ft_isdigit(line[*i + num_len]))
			num_len++;
		if (num_len)
			*d += (double)ft_atoi(line + *i) / pow(10, num_len);
		else
			return (1);
	}
	*i += num_len;
	return (0);
}

int	def_rgb(char *line, int *i, int *rgb, double alpha)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		if (!ft_isdigit(line[*i]))
			return (1);
		rgb[j] = ft_atoi(line + *i) * alpha;
		while (ft_isdigit(line[*i]))
			(*i)++;
		if (j < 2)
		{
			if (line[*i] != ',')
				return (1);
			(*i)++;
		}
	}
	if (line[*i] != ' ' && line[*i] != '\t' && line[*i])
		return (1);
	return (0);
}
