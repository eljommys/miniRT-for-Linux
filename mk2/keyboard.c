/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:58:23 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 15:01:38 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void	change_cam(t_data *param)
{
	if (param->cam.i + 1 == param->cam.n)
		param->cam.i = 0;
	else
		param->cam.i++;
	pos_init(param, param->cam.i);
	vectors_init(param, param->cam.i);
}

static void	key_pressed_ifs(int keycode, t_data *param)
{
	int j;

	j = -1;
	if (keycode == KEY_ESC)
		ft_exit(param);
	else if (keycode == KEY_W)
		while (++j < 3)
			param->cam.o[j] += param->cam.vn[j] * 20;
	else if (keycode == KEY_A)
		while (++j < 3)
			param->cam.o[j] += param->cam.vx[j] * -20;
	else if (keycode == KEY_S)
		while (++j < 3)
			param->cam.o[j] += param->cam.vn[j] * -20;
	else if (keycode == KEY_D)
		while (++j < 3)
			param->cam.o[j] += param->cam.vx[j] * 20;
	else if (keycode == KEY_SPA)
		param->cam.o[2] += 10;
	else if (keycode == KEY_CTR)
		param->cam.o[2] += -10;
	else if (keycode == KEY_ENT)
		save_scr(param);
	else if (keycode == KEY_V)
		change_cam(param);
}

int			key_pressed(int keycode, t_data *param)
{
	param->key = keycode;
	key_pressed_ifs(keycode, param);
	calculate_rotation(param);
	calculate_vectors(param);
	copy_cam(param);
	return (0);
}