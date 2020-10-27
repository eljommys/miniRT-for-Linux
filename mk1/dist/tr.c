/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 21:00:17 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/27 14:08:16 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dist.h"

//Funcion que proyecta en el plano del triangulo el punto en el espacio.

//Funcion que dice donde esta en el espacio proyectado r2 del plano el punto
//proyectado tomando como origen el punto A del triangulo.

//Funcion que dice si el punto proyectado esta dentro del triangulo o no.

//Añadir a misc.c una funcion que se llame:
//		double	segment_dist(double *A, double *B, double *P)
//que calcule la distancia de P a un segmento de recta dado por A y B.

//Si el putno proyectado esta dentro del triangulo coger la distancia al
//plano del triangulo.

//Si no esta dentro del triangulo coger la distancia mas corta a uno de los
//tres segmentos que forman el triangulo.

static void	pl_project(t_data *param, double *P1, int i)
{
	double	ijk[3];
	double	pqr[3];
	double	abc[3];
	int		j;

	j = -1;
	while (++j < 3)
	{
		ijk[j] = param->tr[i]->nor[j];
		pqr[j] = param->tr[i]->A[j];
		abc[j] = param->cam.ray.O[j];
	}
	P1[1] = (ijk[0] * (pqr[0] + ijk[0] * abc[1] / ijk[1] - abc[0]) +
			ijk[2] * (pqr[2] + ijk[2] * abc[1] / ijk[1] - abc[2]) +
			ijk[1] * pqr[1]) / ((pow(ijk[0], 2) + pow(ijk[2], 2)) / ijk[1] +
								ijk[1]);
	P1[0] = (P1[1] - abc[1]) * ijk[0] / ijk[1] + abc[0];
	P1[2] = (P1[1] - abc[1]) * ijk[2] / ijk[1] + abc[2];
}

static int	is_inside(t_data *param, double *P1, int i)
{
	double	w[2];
	double	ac[3];
	double	ab[3];
	double	ap[3];
	double	A[3];
	int		j;
	int 	x;
	int 	y;

	if (!param->tr[i]->nor[2])
	{
		if (!param->tr[i]->nor[1])
			x = 1;
		else
			x = 0;
		y = 2;
	}
	else
	{
		x = 0;
		y = 1;
	}
	j = -1;
	while (++j < 3)
	{
		ab[j] = param->tr[i]->ab[j];
		ac[j] = param->tr[i]->ac[j];
		ap[j] = param->cam.ray.O[j] - param->tr[i]->A[j];
		A[j] = param->tr[i]->A[j];
	}
	/*w[0] = (ac[x] * (A[y] - P1[y]) + ac[y] * (P1[x] - A[x])) /
			(ab[x] * ac[y] + ab[y] * ac[x]);
	w[1] = (P1[y] - A[y] - w[0] * ab[y]) / ac[y];*/
	w[1] = (dot_2d(ap, ac, x, y) * dot_2d(ac, ab, x, y) - dot_2d(ap, ab, x, y) * dot_2d(ac, ac, x, y)) /
			(dot_2d(ab, ac, x, y) * dot_2d(ac, ab, x, y) - dot_2d(ab, ab, x, y) * dot_2d(ac, ac, x, y));
	w[0] = (dot_2d(ap, ac, x, y) - w[1] * dot_2d(ab, ac, x, y)) /
			dot_2d(ac, ac, x, y);
	if (w[0] >= 0 && w[0] < 1 && w[1] >= 0 && w[1] < 1 && w[0] + w[1] <= 1)
		return (1);
	return (0);
}

static double	contour_dist(t_data *param, int i)
{
	double	aux;
	double	dist;

	dist = segment_dist(param->tr[i]->A, param->tr[i]->B, param->cam.ray.O);
	aux = segment_dist(param->tr[i]->B, param->tr[i]->C, param->cam.ray.O);
	dist = (aux < dist) ? aux : dist;
	aux = segment_dist(param->tr[i]->C, param->tr[i]->A, param->cam.ray.O);
	dist = (aux < dist) ? aux : dist;
	return (dist);
}

double 		tr_dist(t_data *param)
{
	int i;
	int j;
	double	aux;
	double	dist;
	double	P1[3];

	i = -1;
	dist = 2147483647;
	while (param->tr[++i])
	{
		pl_project(param, P1, i);
		aux = (is_inside(param, P1, i)) ?
			plane_dist(param->tr[i]->nor, param->tr[i]->A, param->cam.ray.O) :
			contour_dist(param, i);
		//aux = contour_dist(param, i);
		param->cam.ray.obj_n = (aux < dist) ? i : param->cam.ray.obj_n;
		dist = (aux < dist) ? aux : dist;
	}
	return (dist);
}
