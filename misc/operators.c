/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:25:03 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 13:25:48 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

double	max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
