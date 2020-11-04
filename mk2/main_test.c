/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:30:40 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:16:03 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void		print_scene(t_data *param)
{
	int n;
	int i;
	int rgb[3];

	n = 0;
	printf("\n--R: %d x %d\n", param->scr.x, param->scr.y);
	printf("--A: %d %d %d\n\n", param->amb_l_rgb[0], param->amb_l_rgb[1], param->amb_l_rgb[2]);
	i = -1;
	while (param->l[++i])
	{
		hex_to_rgb(param->l[i]->col, rgb);
		printf("%d. l: P(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->l[i]->o[0], param->l[i]->o[1], param->l[i]->o[2],
			rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->c[++i])
	{
		printf("%d. c: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) fov(%d)\n",
			++n, param->c[i]->o[0], param->c[i]->o[1], param->c[i]->o[2],
			param->c[i]->v[0], param->c[i]->v[1], param->c[i]->v[2],
			param->c[i]->fov);
	}
	i = -1;
	while (param->sp[++i])
	{
		hex_to_rgb(param->sp[i]->col, rgb);
		printf("%d. sp: P(%.1f %.1f %.1f) d(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->sp[i]->o[0], param->sp[i]->o[1], param->sp[i]->o[2],
			param->sp[i]->r * 2, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->pl[++i])
	{
		hex_to_rgb(param->pl[i]->col, rgb);
		printf("%d. pl: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->pl[i]->o[0], param->pl[i]->o[1], param->pl[i]->o[2],
			param->pl[i]->v[0], param->pl[i]->v[1], param->pl[i]->v[2],
			rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->cy[++i])
	{
		hex_to_rgb(param->cy[i]->col, rgb);
		printf("%d. cy: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) d(%.1f) h(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->cy[i]->o[0], param->cy[i]->o[1], param->cy[i]->o[2],
			param->cy[i]->v[0], param->cy[i]->v[1], param->cy[i]->v[2],
			param->cy[i]->d, param->cy[i]->h, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->sq[++i])
	{
		hex_to_rgb(param->sq[i]->col, rgb);
		printf("%d. sq: P(%.1f %.1f %.1f) v(%.1f %.1f %.1f) h(%.1f) rgb(%03d %03d %03d)\n",
			++n, param->sq[i]->o[0], param->sq[i]->o[1], param->sq[i]->o[2],
			param->sq[i]->v[0], param->sq[i]->v[1], param->sq[i]->v[2],
			param->sq[i]->h, rgb[0], rgb[1], rgb[2]);
	}
	i = -1;
	while (param->tr[++i])
	{
		hex_to_rgb(param->tr[i]->col, rgb);
		printf("%d. tr: A(%.1f %.1f %.1f) B(%.1f %.1f %.1f) C(%.1f %.1f %.1f) rgb(%03d %03d %03d)\n",
			++n, param->tr[i]->a[0], param->tr[i]->a[1], param->tr[i]->a[2],
			param->tr[i]->b[0], param->tr[i]->b[1], param->tr[i]->b[2],
			param->tr[i]->c[0], param->tr[i]->c[1], param->tr[i]->c[2],
			rgb[0], rgb[1], rgb[2]);
	}
}

static void	ft_hooks(t_data *param)
{
	mlx_hook(param->win_id, KEY_PR, MK_KEY_PR, key_pressed, param);
	mlx_hook(param->win_id, BUT_PR, MK_BUT_PR, button_pressed, param);
	mlx_hook(param->win_id, BUT_RE, MK_BUT_RE, button_released, param);
	mlx_hook(param->win_id, MOT_NT, MK_PTR_MO, get_pos, param);
	mlx_hook(param->win_id, CLI_MG, CL_CLOSE, ft_exit, param);
	mlx_loop_hook(param->id, show_obj, param);
}

/*
**	queda gestionar errores de archivo
**	-	solo se puede declarar una vez R y A
**	-	la resolucion, los rgb, la intensidad, altura y diametro
**			no pueden ser negativos
**	-	el tamaño maximo de resolucion es el del display
**	-	los floats estan separados por puntos solamente
**	-	los rgb estan separados por comas solamente
**	-	el fov de camara tiene que estar entre 0 y 179
**	-	comprobar que los argumentos son los que deben
*/

int			main(int argc, char **argv)
{
	t_data *param;
	int		i;

	if (argc == 2 || argc == 3)
	{
		i = ft_strlen(argv[1]);
		if (ft_memcmp(argv[1] + i - 3, ".rt", 3))
		{
			write(1, "Please insert correct .rt file\n", 32);
			return (-1);
		}
		param = (t_data *)malloc(sizeof(t_data));
		ft_init(param, argv);
		print_scene(param);
		ft_hooks(param);
		if (argc == 3)
		{
			if (!ft_memcmp(argv[2], "--save", 7))
				save_scr(param);
			else
				write(1, "Enter --save if you want to save a screenshot\n", 47);
			ft_exit(param);
		}
		mlx_loop(param->id);
	}
	else
		write(1, "Wrong number of arguments!\n", 28);
	return (0);
}
