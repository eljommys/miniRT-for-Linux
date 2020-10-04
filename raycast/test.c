/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:15:22 by marvin            #+#    #+#             */
/*   Updated: 2020/09/23 14:15:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	gcc -o unit_test *.c ../minilibx-linux/*.a -lm -lbsd -lX11 -lXext
*/

#include "raycast.h"

printf_val(camera *def)
{
	fflush(stdout);
	printf("\rOrigen --> X: %d, Y: %d, Z: %d\t", def->O[0], def->O[1], def->O[2]);
	printf("Punto --> X: %d, Y: %d, Z: %d", def->P[0], def->P[1], def->P[2]);
}

int main(void)
{
	while (1)
	{
		if ()
	}
	return (0);	
}
