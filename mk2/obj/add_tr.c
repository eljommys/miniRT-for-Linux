/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:48:44 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 15:47:57 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void cpy_tr(t_triangle **tr, t_triangle **aux, int i)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[i]->A[j] = tr[i]->A[j];
		aux[i]->B[j] = tr[i]->B[j];
		aux[i]->C[j] = tr[i]->C[j];
		aux[i]->ab[j] = tr[i]->ab[j];
		aux[i]->ac[j] = tr[i]->ac[j];
		aux[i]->nor[j] = tr[i]->nor[j];
	}
	aux[i]->col = tr[i]->col;
}

static void new_tr(t_triangle **aux, double *A, double *B, double *C, int *var)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		aux[var[0]]->A[j] = A[j];
		aux[var[0]]->B[j] = B[j];
		aux[var[0]]->C[j] = C[j];
		aux[var[0]]->ab[j] = B[j] - A[j];
		aux[var[0]]->ac[j] = C[j] - A[j];
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

t_triangle	**add_tr(t_triangle **tr, double *A, double *B, double *C, int c)
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
			new_tr(aux, A, B, C, var);
	}
	aux[var[0]] = 0;
	var[0] = 0;
	if (var[2])
		while (tr[var[0]])
			free(tr[var[0]++]);
	free(tr);
	return (aux);
}
