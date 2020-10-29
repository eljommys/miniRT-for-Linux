/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:26:09 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 13:26:39 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

double	plane_dist(double *v, double *o, double *p)
{
	return (fabs(v[0] * p[0] + v[1] * p[1] + v[2] * p[2] -
				(v[0] * o[0] + v[1] * o[1] + v[2] * o[2])));
}

double	segment_dist(double *A, double *B, double *p)
{
	double	h;
	double	d[3];
	double	pa[3];
	double	ba[3];
	int		j;

	j = -1;
	while (++j < 3)
	{
		pa[j] = A[j] - p[j];
		ba[j] = A[j] - B[j];
	}
	h = min(1, max(0, dot_prod(pa, ba) / pow(mod(ba), 2)));
	j = -1;
	while (++j < 3)
		d[j] = pa[j] - h * ba[j];
	return (mod(d));
}
