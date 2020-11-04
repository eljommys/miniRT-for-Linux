/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:48:06 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 17:20:36 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	cpy_sp(t_sphere  **sp, t_sphere **aux, int i)
{
	int j;

	j = -1;
	while (++j < 3)
		aux[i]->o[j] = sp[i]->o[j];
	aux[i]->r = sp[i]->r;
	aux[i]->col = sp[i]->col;
}

static void	new_sp(t_sphere **aux, double *o, double r, int *var)
{
	int j;

	j = -1;
	while (++j < 3)
		aux[var[2]]->o[j] = o[j];
	aux[var[2]]->r = r;
	aux[var[2]]->col = var[1];
}

static int	sp_init(t_sphere **sp, t_sphere ***aux, int *var, int c)
{
	var[0] = 0;
	var[1] = c;
	while (sp[var[0]])
		var[0]++;
	if (!(*aux = (t_sphere **)malloc(sizeof(t_sphere *) * (var[0] + 2))))
		return (1);
	return (0);
}

/*
**	var[3] = len, c, i
*/

t_sphere	**add_sp(t_sphere **sp, double *o, double r, int c)
{
	t_sphere	**aux;
	int			var[3];

	if (sp_init(sp, &aux, var, c))
		return (sp);
	var[2] = -1;
	while(++var[2] < var[0] + 1)
	{
		aux[var[2]] = (t_sphere *)malloc(sizeof(t_sphere));
		if (var[2] < var[0])
			cpy_sp(sp, aux, var[2]);
		else
			new_sp(aux, o, r, var);
	}
	aux[var[2]] = 0;
	var[2] = 0;
	if (var[0])
		while (sp[var[2]])
			free(sp[var[2]++]);
	free(sp);
	return (aux);
}
