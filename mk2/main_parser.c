/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:56:46 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 17:23:41 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void 	print_scene(t_data *param)
{
	int n;
	int i;
	int j;
	int rgb[3];

	n = 0;
	printf("\n--R: %d x %d\n", param->scr.x, param->scr.y);
	printf("--A: %d %d %d\n\n", param->amb_l_rgb[0], param->amb_l_rgb[1], param->amb_l_rgb[2]);
	i = -1;
	while (param->l[++i])
	{
		hex_to_rgb(param->l[i]->col, rgb);
		printf("%d. l: P(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->l[i]->O[0], param->l[i]->O[1], param->l[i]->O[2],
			rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->sp[++i])
	{
		hex_to_rgb(param->sp[i]->col, rgb);
		printf("%d. sp: P(%.1f %.1f %.1f) d(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->sp[i]->O[0], param->sp[i]->O[1], param->sp[i]->O[2],
			param->sp[i]->r * 2, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->pl[++i])
	{
		hex_to_rgb(param->pl[i]->col, rgb);
		printf("%d. pl: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->pl[i]->O[0], param->pl[i]->O[1], param->pl[i]->O[2],
			param->pl[i]->v[0], param->pl[i]->v[1], param->pl[i]->v[2],
			rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->cy[++i])
	{
		hex_to_rgb(param->cy[i]->col, rgb);
		printf("%d. cy: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) d(%.1f) h(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->cy[i]->O[0], param->cy[i]->O[1], param->cy[i]->O[2],
			param->cy[i]->v[0], param->cy[i]->v[1], param->cy[i]->v[2],
			param->cy[i]->d, param->cy[i]->h, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->sq[++i])
	{
		hex_to_rgb(param->sq[i]->col, rgb);
		printf("%d. sq: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) h(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->sq[i]->O[0], param->sq[i]->O[1], param->sq[i]->O[2],
			param->sq[i]->v[0], param->sq[i]->v[1], param->sq[i]->v[2],
			param->sq[i]->h, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->tr[++i])
	{
		hex_to_rgb(param->tr[i]->col, rgb);
		printf("%d. tr: A(%.1f %.1f %.1f) B(%.1f %.1f %.1f) C(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->tr[i]->A[0], param->tr[i]->A[1], param->tr[i]->A[2],
			param->tr[i]->B[0], param->tr[i]->B[1], param->tr[i]->B[2],
			param->tr[i]->C[0], param->tr[i]->C[1], param->tr[i]->C[2],
			rgb[0], rgb[1], rgb[2]);
	}
}

int			main(int argc, char **argv)
{
	t_data *param;

	param = (t_data *)malloc(sizeof(t_data));
	ft_init(param, argv);
	print_scene(param);
	return (0);
}
