/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:16:32 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 16:42:40 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	cpy_c(t_cams **c, t_cams **aux, int i)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->o[j] = c[i]->o[j];
		aux[i]->v[j] = c[i]->v[j];
	}
	aux[i]->fov = c[i]->fov;
}

static void	new_c(t_cams **aux, double **o_v, int fov, int i)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->o[j] = o_v[0][j];
		aux[i]->v[j] = o_v[1][j];
	}
	aux[i]->fov = fov;
}

static void	set_c(t_cams **c, t_cams **aux, double **o_v, int fov)
{
	int i;
	int len;

	len = 0;
	while (c[len])
		len++;
	i = -1;
	while (++i < len + 1)
	{
		aux[i] = (t_cams *)malloc(sizeof(t_cams));
		if (i < len)
			cpy_c(c, aux, i);
		else
			new_c(aux, o_v, fov, i);
	}
	aux[i] = 0;
}

t_cams		**add_c(t_cams **c, double **o_v, int fov)
{
	int		i;
	int		len;
	t_cams	**aux;

	len = 0;
	while (c[len])
		len++;
	if (!(aux = (t_cams **)malloc(sizeof(t_cams *) * len)))
		return (c);
	norm(o_v[1], o_v[1]);
	set_c(c, aux, o_v, fov);
	i = 0;
	if (len)
		while (c[i])
			free(c[i++]);
	free(c);
	return (aux);
}
