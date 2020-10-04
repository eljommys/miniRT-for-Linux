/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseMotion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:25:07 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/04 18:09:38 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"


//	gcc -o unit_test mouseMotion.c raycast.c ../minilibx-linux-master/*.a -L.. -lmlx -lXext -lX11 -lm -lbsd

static void		mouse_init(t_data *param)
{
	param->x = 0;
	param->y = 0;
	param->mouse_x = 0;
	param->mouse_y = 0;
}

static void		screen_init(t_data *param)
{
	param->resolution_x = 700;
	param->resolution_y = 500;
	param->id = mlx_init();
	param->win_id = mlx_new_window(param->id, param->resolution_x,
								param->resolution_y, "hola");
	param->img = mlx_new_image(param->id, param->resolution_x,
								param->resolution_y);
	param->addr = mlx_get_data_addr(param->img, &param->bits_per_pixel,
								&param->line_length, &param->endian);
}

static void		vectors_init(t_data *param)
{
	int		i;
	double	module;

	param->O[0] = 0;
	param->O[1] = 0;
	param->O[2] = 0;
	param->Vn[0] = 1;
	param->Vn[1] = 0;
	param->Vn[2] = 0;
	module = sqrt(pow(param->Vn[0], 2) + pow(param->Vn[1], 2) + pow(param->Vn[2], 2));
	i = -1;
	while (++i < 3)
		param->Vn[i] /= module;
	if (param->Vn[0] >= 0 && param->Vn[1] >= 0)
		param->rotation_z_axis = asin(param->Vn[1]);
	else if (param->Vn[0] < 0 && param->Vn[1] >= 0)
		param->rotation_z_axis = M_PI - asin(param->Vn[1]);
	else if (param->Vn[0] < 0 && param->Vn[1] < 0)
		param->rotation_z_axis = M_PI + asin(param->Vn[1]);
	else if (param->Vn[0] >= 0 && param->Vn[1] < 0)
		param->rotation_z_axis = 2 * M_PI - asin(param->Vn[1]);
	param->rotation_y_axis = (param->Vn[2] >= 0) ? asin(param->Vn[2]) :
			2 * M_PI - asin(param->Vn[2]);
	param->fov = 144;
	param->screen_dist = (param->resolution_x / 2) /
						tan((param->fov / 2) * M_PI / 180);
}

void	ft_init(t_data *param)
{
	mouse_init(param);
	screen_init(param);
	vectors_init(param);
}

int		ft_exit(t_data *param)
{
	free(param);
	exit(0);
	return (0);
}

int		get_pos(int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->x = param->mouse_x + x - param->resolution_x / 2;
		param->y = -(param->mouse_y + y - param->resolution_y / 2);
		calculate_rotation(param);
		calculate_vectors(param);

		printf("X: %d, Y: %d\n", param->x, param->y);
		printf("Screen dist: %f\n", param->screen_dist);
		printf("Vn[x]: %f, Vn[y]: %f, Vn[z]: %f\n\n\n", param->Vn[0], param->Vn[1], param->Vn[2]);
	}
	return (0);
}

int		button_pressed(int button, int x, int y, t_data *param)
{
	param->button = button;
	if (button == 1)
	{
		mlx_mouse_hide(param->id, param->win_id);
		mlx_mouse_move(param->id, param->win_id, param->resolution_x / 2, param->resolution_y / 2);
		param->aux_x = x;
		param->aux_y = y;
	}
	else if (button == 3)
	{
		vectors_init(param);
		mouse_init(param);
		calculate_rotation(param);
		calculate_vectors(param);
	}
	printf("button = %d\n", button);
	return (0);
}

int		button_released(int button, int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->mouse_x += (x - param->resolution_x / 2);
		param->mouse_y += (y - param->resolution_y / 2);
		mlx_mouse_move(param->id, param->win_id, param->aux_x, param->aux_y);
		mlx_mouse_show(param->id, param->win_id);
	}
	param->button = 0;
	return (0);
}

int		key_pressed(int keycode, t_data *param)
{
	if (keycode == KEY_ESC)
		ft_exit(param->id);
	else if (keycode == KEY_W)
	{
		param->O[0] += param->Vn[0] * 3;
		param->O[1] += param->Vn[1] * 3;
		param->O[2] += param->Vn[2] * 3;
	}
	else if (keycode == KEY_A)
	{
		param->O[0] += param->Vx[0] * -3;
		param->O[1] += param->Vx[1] * -3;
		param->O[2] += param->Vx[2] * -3;
	}
	else if (keycode == KEY_S)
	{
		param->O[0] += param->Vn[0] * -3;
		param->O[1] += param->Vn[1] * -3;
		param->O[2] += param->Vn[2] * -3;
	}
	else if (keycode == KEY_D)
	{
		param->O[0] += param->Vx[0] * 3;
		param->O[1] += param->Vx[1] * 3;
		param->O[2] += param->Vx[2] * 3;
	}
	else if (keycode == KEY_SPA)
		param->O[2] += 3;
	else if (keycode == KEY_CTR)
		param->O[2] += -3;
	printf("key = %x\n", keycode);
	return (0);
}

int ft_loop(t_data *param)
{
	//show_camera(param); // solo para pruebas
	show_pov(param);
	return (0);
}

/*
** ****************************************************************************
** *************************FUNCIONES DE PRUEBA********************************
** ****************************************************************************
*/

int		main(void)
{
	t_data *param;

	param = (t_data *)malloc(sizeof(t_data));
	ft_init(param);
	mlx_hook(param->win_id, KEY_PR, MK_KEY_PR, key_pressed, param);
	mlx_hook(param->win_id, BUT_PR, MK_BUT_PR, button_pressed, param);
	mlx_hook(param->win_id, BUT_RE, MK_BUT_RE, button_released, param);
	mlx_hook(param->win_id, MOT_NT, MK_PTR_MO, get_pos, param);
	mlx_hook(param->win_id, CLI_MG, CL_CLOSE, ft_exit, param);
	mlx_loop_hook(param->id, ft_loop, param);
	mlx_loop(param->id);
	return (0);
}
