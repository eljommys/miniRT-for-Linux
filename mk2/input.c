/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:25:20 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/31 17:02:19 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

int		get_pos(int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->reload = 1;
		param->crd.x = param->mou.x + x - param->scr.x / 2;
		param->crd.y = -(param->mou.y + y - param->scr.y / 2);
		if (param->crd.y > 249)
		{
			param->crd.y = 245;
			mlx_mouse_move(param->id, param->win_id, x,
						param->scr.y / 2 - param->crd.y);
		}
		else if (param->crd.y < -249)
		{
			param->crd.y = -245;
			mlx_mouse_move(param->id, param->win_id, x,
						param->scr.y / 2 - param->crd.y);
		}
		calculate_rotation(param);
		calculate_vectors(param);
		copy_cam(param);

		printf("X: %d, Y: %d\n", param->crd.x, param->crd.y);
		printf("Screen dist: %f\n", param->scr.dist);
		printf("Vn[x]: %f, Vn[y]: %f, Vn[z]: %f\n", param->cam.Vn[0],
									param->cam.Vn[1], param->cam.Vn[2]);
		printf("O = (%f, %f, %f)\n\n\n", param->cam.O[0], param->cam.O[1],
										param->cam.O[2]);
	}
	return (0);
}

int		button_pressed(int button, int x, int y, t_data *param)
{
	param->button = button;
	if (param->key == KEY_ENT)
		param->key = 0;
	if (button == 1)
	{
		mlx_mouse_hide(param->id, param->win_id);
		mlx_mouse_move(param->id, param->win_id, param->scr.x / 2,
						param->scr.y / 2);
		param->crd.aux_x = x;
		param->crd.aux_y = y;
	}
	else if (button == 3)
	{
		vectors_init(param, param->cam.i);
		mouse_init(param);
		calculate_rotation(param);
		calculate_vectors(param);
		copy_cam(param);
		printf("RESET\n");
	}
	return (0);
}

int		button_released(int button, int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->mou.x += (x - param->scr.x / 2);
		param->mou.y += (y - param->scr.y / 2);
		mlx_mouse_move(param->id, param->win_id, param->crd.aux_x,
						param->crd.aux_y);
		mlx_mouse_show(param->id, param->win_id);
	}
	param->button = 0;
	return (0);
}

static void change_cam(t_data *param)
{
	if (param->cam.i + 1 == param->cam.n)
		param->cam.i = 0;
	else
		param->cam.i++;
	pos_init(param, param->cam.i);
	vectors_init(param, param->cam.i);
}

int		key_pressed(int keycode, t_data *param)
{
	int	j;

	param->key = keycode;
	param->reload = 1;
	j = -1;
	if (keycode == KEY_ESC)
		ft_exit(param->id);
	else if (keycode == KEY_W)
		while(++j < 3)
			param->cam.O[j] += param->cam.Vn[j] * 20;
	else if (keycode == KEY_A)
		while(++j < 3)
			param->cam.O[j] += param->cam.Vx[j] * -20;
	else if (keycode == KEY_S)
		while(++j < 3)
			param->cam.O[j] += param->cam.Vn[j] * -20;
	else if (keycode == KEY_D)
		while(++j < 3)
			param->cam.O[j] += param->cam.Vx[j] * 20;
	else if (keycode == KEY_SPA)
		param->cam.O[2] += 10;
	else if (keycode == KEY_CTR)
		param->cam.O[2] += -10;
	else if (keycode == KEY_ENT)
		show_obj(param);
	else if (keycode == KEY_V)
		change_cam(param);
	printf("key = %x\n", keycode);
	calculate_rotation(param);
	calculate_vectors(param);
	copy_cam(param);
	return (0);
}
