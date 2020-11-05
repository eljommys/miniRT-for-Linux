/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:01:13 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:35:47 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

double	dot_2d(double *u, double *v, int x, int y)
{
	return (u[x] * v[x] + u[y] * v[y]);
}

void	norm(double *u, double *v)
{
	int		j;
	double	module;

	j = -1;
	module = mod(u);
	while (++j < 3)
		v[j] = u[j] / module;
}
