/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:58:50 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 13:01:36 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

double	mod(double *v)
{
	return (sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2)));
}

double	cross_prod(double *u, double *v, int i)
{
	if (i == 0)
		return (u[1] * v[2] - u[2] * v[1]);
	else if (i == 1)
		return (u[2] * v[0] - u[0] * v[2]);
	else if (i == 2)
		return (u[0] * v[1] - u[1] * v[0]);
	else
		return (0);
}

double	dot_prod(double *u, double *v)
{
	return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);
}

double	dot2_prod(double *u)
{
	return (dot_prod(u, u));
}
