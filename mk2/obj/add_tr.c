/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:48:44 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 16:55:37 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	cpy_tr(t_triangle **tr, t_triangle **aux, int i)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->a[j] = tr[i]->a[j];
		aux[i]->b[j] = tr[i]->b[j];
		aux[i]->c[j] = tr[i]->c[j];
		aux[i]->ab[j] = tr[i]->ab[j];
		aux[i]->ac[j] = tr[i]->ac[j];
		aux[i]->nor[j] = tr[i]->nor[j];
	}
	aux[i]->col = tr[i]->col;
}

static void	new_tr(t_triangle **aux, double **abc, int *var)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[var[0]]->a[j] = abc[0][j];
		aux[var[0]]->b[j] = abc[1][j];
		aux[var[0]]->c[j] = abc[2][j];
		aux[var[0]]->ab[j] = abc[1][j] - abc[0][j];
		aux[var[0]]->ac[j] = abc[2][j] - abc[0][j];
	}
	j = -1;
	while (++j < 3)
		aux[var[0]]->nor[j] = cross_prod(aux[var[0]]->ab, aux[var[0]]->ac, j);
	norm(aux[var[0]]->nor, aux[var[0]]->nor);
	aux[var[0]]->col = var[1];
}

/*
**	var[3] = i, c, len
*/

t_triangle	**add_tr(t_triangle **tr, double **abc, int c)
{
	t_triangle	**aux;
	int			var[3];

	var[2] = 0;
	while (tr[var[2]])
		var[2]++;
	if (!(aux = (t_triangle **)malloc(sizeof(t_triangle *) * (var[2] + 2))))
		return (tr);
	var[1] = c;
	var[0] = -1;
	while(++var[0] < var[2] + 1)
	{
		aux[var[0]] = (t_triangle *)malloc(sizeof(t_triangle));
		if (var[0] < var[2])
			cpy_tr(tr, aux, var[1]);
		else
			new_tr(aux, abc, var);
	}
	aux[var[0]] = 0;
	var[0] = 0;
	if (var[2])
		while (tr[var[0]])
			free(tr[var[0]++]);
	free(tr);
	return (aux);
}
