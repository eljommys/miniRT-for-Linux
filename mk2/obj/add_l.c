/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:23:06 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/01 13:54:20 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	set_l(t_light **l, t_light **aux, double *O, int *var)
{
	int	i;
	int	j;

	i = -1;
	while(++i < var[0] + 1)
	{
		aux[i] = (t_light *)malloc(sizeof(t_light));
		j = -1;
		if (i < var[0])
		{
			while (++j < 3)
			{
				aux[i]->O[j] = l[i]->O[j];
				aux[i]->rgb[j] = l[i]->rgb[j];
			}
			aux[i]->col = l[i]->col;
		}
		else
		{
			while (++j < 3)
				aux[i]->O[j] = O[j];
			hex_to_rgb(var[1], (int *)aux[i]->rgb);
			aux[i]->col = var[1];
		}
	}
	aux[i] = 0;
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
