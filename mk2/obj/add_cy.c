/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:51:46 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:12:59 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void cpy_cy(t_cylinder **cy, t_cylinder **aux, int i)
{
	int	j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->o[j] = cy[i]->o[j];
		aux[i]->v[j] = cy[i]->v[j];
	}
	aux[i]->col = cy[i]->col;
	aux[i]->d = cy[i]->d;
	aux[i]->h = cy[i]->h;
}

static void	new_cy(t_cylinder **aux, double *O, double *v, double *dim, int *var)
{
	int		j;
	double	Vn[3];

	norm(v, Vn);
	j = -1;
	while (++j < 3)
	{
		aux[var[0]]->o[j] = O[j];
		aux[var[0]]->v[j] = Vn[j];
	}
	aux[var[0]]->col = var[1];
	aux[var[0]]->d = dim[0];
	aux[var[0]]->h = dim[1];
}

static t_cylinder	**init_sq(t_cylinder **cy, int *var)
{
	t_cylinder **aux;

	var[2] = 0;
	while (cy[var[2]])
		var[2]++;
	if (!(aux = (t_cylinder **)malloc(sizeof(t_cylinder *) * (var[2] + 2))))
		return (0);
	return (aux);
}

/*
**	var = i, c, len
**	dim = h, d
*/

t_cylinder	**add_cy(t_cylinder **cy, double *O, double *v, double h, double d,
					int c)
{
	t_cylinder	**aux;
	int			var[3];
	double		dim[2];

	if (!(aux = init_sq(cy, var)))
		return (cy);
	var[0] = -1;
	var[1] = c;
	dim[0] = h;
	dim[1] = d;
	while(++var[0] < var[2] + 1)
	{
		aux[var[0]] = (t_cylinder *)malloc(sizeof(t_cylinder));
		if (var[0] < var[2])
			cpy_cy(cy, aux, var[0]);
		else
			new_cy(aux, O, v, dim, var);
	}
	aux[var[0]] = 0;
	var[0] = 0;
	if (var[2])
		while (cy[var[0]])
			free(cy[var[0]++]);
	free(cy);
	return (aux);
}
