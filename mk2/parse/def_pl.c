/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:47:58 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 11:53:18 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void def_P(char *line, int *i, double *P)
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
		while ('0' <= line[*i + num_len] && line[*i + num_len] <= '9')
			num_len++;
		P[j] += (double)ft_atoi(line + *i) / pow(10, num_len);
		*i += num_len + 1;
	}
}

static void	def_rgb(char *line, int *i, int *rgb)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		rgb[j] = ft_atoi(line + *i);
		while ('0' <= line[*i] && line[*i] <= '9')
			(*i)++;
		(*i)++;
	}
}

void		def_pl(t_data *param, char *line)
{
	int		i;
	double	P[3];
	double	v[3];
	int		rgb[3];
	int		c;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_P(line, &i, P);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_P(line, &i, v);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	def_rgb(line, &i, rgb);
	rgb_to_hex(rgb, &c);
	param->pl = add_pl(param->pl, P, v, c);
}
