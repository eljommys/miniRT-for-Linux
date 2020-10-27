/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:33:45 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/27 16:41:38 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void set_pl(t_plane **pl, t_plane **aux, double *O, double *v, int *var)
{
	int	i;
	int	j;

	i = -1;
	while(++i < var[0] + 1)
	{
		aux[i] = (t_plane *)malloc(sizeof(t_plane));
		j = -1;
		if (i < var[0])
		{
			while (++j < 3)
			{
				aux[i]->O[j] = pl[i]->O[j];
				aux[i]->v[j] = pl[i]->v[j];
			}
			aux[i]->col = pl[i]->col;
		}
		else
		{
			while (++j < 3)
			{
				aux[i]->O[j] = O[j];
				aux[i]->v[j] = v[j];
			}
			aux[i]->col = var[1];
		}
	}
	aux[i] = 0;
}

t_plane		**add_pl(t_plane **pl, double *O, double *v, int c)
{
	t_plane		**aux;
	double		Vn[3];
	int			var[2];
	int			i;

	var[0] = 0;
	var[1] = c;
	while (pl[var[0]])
		var[0]++;
	if (!(aux = (t_plane **)malloc(sizeof(t_plane *) * (var[0] + 2))))
		return (pl);
	i = -1;
	while (++i < 3)
		Vn[i] = v[i] / mod(v);
	set_pl(pl, aux, O, Vn, var);
	i = 0;
	if (var[0])
		while (pl[i])
			free(pl[i++]);
	free(pl);
	return (aux);
}
