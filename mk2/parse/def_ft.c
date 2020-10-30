/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:15:51 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 17:16:13 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def_ft.h"

void def_P(char *line, int *i, double *P)
{
	int j;
	int num_len;

	j = -1;
	while (++j < 3)
	{
		P[j] = (double)ft_atoi(line + *i);
		while ('0' <= line[*i] && line[*i] <= '9')
			(*i)++;
		(*i)++;
		num_len = 0;
		while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9' ||
				line[*i + num_len] == '-')
			num_len++;
		P[j] += (double)ft_atoi(line + *i) / pow(10, num_len);
		*i += num_len + 1;
	}
}

void def_d(char *line, int *i, double *d)
{
	int num_len;

	*d = (double)ft_atoi(line + *i);
	while ('0' <= line[*i] && line[*i] <= '9')
		(*i)++;
	(*i)++;
	num_len = 0;
	while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9' ||
				line[*i + num_len] == '-')
		num_len++;
	*d += (double)ft_atoi(line + *i) / pow(10, num_len);
	*i += num_len;
}

void	def_rgb(char *line, int *i, int *rgb)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		rgb[j] = ft_atoi(line + *i);
		while ('0' <= line[*i] && line[*i] <= '9' ||
				line[*i] == '-')
			(*i)++;
		(*i)++;
	}
}
