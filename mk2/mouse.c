/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:25:20 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:58:48 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

int			get_pos(int x, int y, t_data *param)
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
	}
	return (0);
}

int			button_pressed(int button, int x, int y, t_data *param)
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
	}
	return (0);
}

int			button_released(int button, int x, int y, t_data *param)
{
	if (button == 1)
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
