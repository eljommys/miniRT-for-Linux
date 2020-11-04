/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:16:32 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:12:30 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	set_c(t_cams **c, t_cams **aux, double *O, double *v, int fov)
{
	int i;
	int len;
	int j;

	len = 0;
	while (c[len])
		len++;
	i = -1;
	while (++i < len + 1)
	{
		aux[i] = (t_cams *)malloc(sizeof(t_cams));
		j = -1;
		if (i < len)
		{
			while (++j < 3)
			{
				aux[i]->o[j] = c[i]->o[j];
				aux[i]->v[j] = c[i]->v[j];
			}
			aux[i]->fov = c[i]->fov;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->o[j] = O[j];
				aux[i]->v[j] = v[j];
			}
			aux[i]->fov = fov;
		}
	}
	aux[i] = 0;
}

t_cams		**add_c(t_cams **c, double *O, double *v, int fov)
{
	int		i;
	int		len;
	double	Vn[3];
	t_cams	**aux;

	len = 0;
	while (c[len])
		len++;
	if (!(aux = (t_cams **)malloc(sizeof(t_cams *) * len)))
		return (c);
	norm(v, Vn);
	set_c(c, aux, O, v, fov);
	i = 0;
	if (len)
		while (c[i])
			free(c[i++]);
	free(c);
	return (aux);
}
