/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:48:06 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:13:51 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	set_sp(t_sphere **sp, t_sphere **aux, double *O, double r, int *var)
{
	int	i;
	int	j;

	i = -1;
	while(++i < var[0] + 1)
	{
		aux[i] = (t_sphere *)malloc(sizeof(t_sphere));
		j = -1;
		if (i < var[0])
		{
			while (++j < 3)
				aux[i]->o[j] = sp[i]->o[j];
			aux[i]->r = sp[i]->r;
			aux[i]->col = sp[i]->col;
		}
		else
		{
			while (++j < 3)
				aux[i]->o[j] = O[j];
			aux[i]->r = r;
			aux[i]->col = var[1];
		}
	}
	aux[i] = 0;
}

t_sphere	**add_sp(t_sphere **sp, double *O, double r, int c)
{
	t_sphere	**aux;
	int			var[2];
	int			i;

	var[0] = 0;
	var[1] = c;
	while (sp[var[0]])
		var[0]++;
	if (!(aux = (t_sphere **)malloc(sizeof(t_sphere *) * (var[0] + 2))))
		return (sp);
	set_sp(sp, aux, O, r, var);
	i = 0;
	if (var[0])
		while (sp[i])
			free(sp[i++]);
	free(sp);
	return (aux);
}
