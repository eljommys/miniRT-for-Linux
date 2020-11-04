/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:42:18 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:14:07 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	cpy_sq(t_square **sq, t_square **aux, int i)
{
	int	j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->o[j] = sq[i]->o[j];
		aux[i]->v[j] = sq[i]->v[j];
		aux[i]->x[j] = sq[i]->x[j];
		aux[i]->y[j] = sq[i]->y[j];
	}
	aux[i]->h = sq[i]->h;
	aux[i]->col = sq[i]->col;
}

static void new_sq(t_square **aux, double *O, double *v, double h, int *var)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[var[0]]->o[j] = O[j];
		aux[var[0]]->v[j] = v[j];
	}
	aux[var[0]]->x[0] = 0;
	aux[var[0]]->x[1] = -v[2];
	aux[var[0]]->x[2] = v[1];
	j = -1;
	while (++j < 3)
		aux[var[0]]->y[j] = cross_prod(v, aux[var[0]]->x, j);
	norm(aux[var[0]]->y, aux[var[0]]->y);
	aux[var[0]]->h = h;
	aux[var[0]]->col = var[1];
}

static t_square **init_sq(t_square **sq, int *var)
{
	t_square **aux;

	var[2] = 0;
	while (sq[var[2]])
		var[2]++;
	if (!(aux = (t_square **)malloc(sizeof(t_square *) * (var[2] + 2))))
		return (0);
	return (aux);
}

/*
**	var[3] = i, c, len
*/

t_square	**add_sq(t_square **sq, double *O, double *v, double h, int c)
{
	t_square	**aux;
	double		Vn[3];
	int			var[3];

	if (!(aux = init_sq(sq, var)))
		return (sq);
	var[1] = c;
	norm(v, Vn);
	var[0] = -1;
	while(++var[0] < var[2] + 1)
	{
		aux[var[0]] = (t_square *)malloc(sizeof(t_square));
		if (var[0] < var[2])
			cpy_sq(sq, aux, var[0]);
		else
			new_sq(aux, O, Vn, h, var);
	}
	aux[var[0]] = 0;
	var[0] = 0;
	if (var[2])
		while (sq[var[0]])
			free(sq[var[0]++]);
	free(sq);
	return (aux);
}
