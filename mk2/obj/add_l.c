/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:23:06 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:13:24 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	set_l(t_light **l, t_light **aux, double *O, int *var)
{
	int	i_j[2];

	i_j[0] = -1;
	while(++i_j[0] < var[0] + 1)
	{
		aux[i_j[0]] = (t_light *)malloc(sizeof(t_light));
		i_j[1] = -1;
		if (i_j[0] < var[0])
		{
			while (++i_j[1] < 3)
			{
				aux[i_j[0]]->o[i_j[1]] = l[i_j[0]]->o[i_j[1]];
				aux[i_j[0]]->rgb[i_j[1]] = l[i_j[0]]->rgb[i_j[1]];
			}
			aux[i_j[0]]->col = l[i_j[0]]->col;
		}
		else
		{
			while (++i_j[1] < 3)
				aux[i_j[0]]->o[i_j[1]] = O[i_j[1]];
			hex_to_rgb(var[1], (int *)aux[i_j[0]]->rgb);
			aux[i_j[0]]->col = var[1];
		}
	}
	aux[i_j[0]] = 0;
}

t_light		**add_l(t_light **l, double *O, int c)
{
	t_light		**aux;
	int			var[2];
	int			i;

	var[0] = 0;
	var[1] = c;
	while (l[var[0]])
		var[0]++;
	if (!(aux = (t_light **)malloc(sizeof(t_light *) * (var[0] + 2))))
		return (l);
	set_l(l, aux, O, var);
	i = 0;
	if (var[0])
		while (l[i])
			free(l[i++]);
	free(l);
	return (aux);
}
