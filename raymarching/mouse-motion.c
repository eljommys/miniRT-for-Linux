/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse-motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:25:07 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/17 13:23:53 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"


//	gcc -o unit_test mouse-motion.c raycast.c ../minilibx-linux-master/*.a -L.. -lmlx -lXext -lX11 -lm -lbsd

static void		mouse_init(t_data *param)
{
	param->crd.x = 0;
	param->crd.y = 0;
	param->mou.x = 0;
	param->mou.y = 0;
	param->mou.speed = 0.25;
}

static void		screen_init(t_data *param)
{
	param->scr.x = 1240;
	param->scr.y = 720;
	param->id = mlx_init();
	param->win_id = mlx_new_window(param->id, param->scr.x,
								param->scr.y, "hola");
	param->img.img = mlx_new_image(param->id, param->scr.x,
								param->scr.y);
	param->img.addr = mlx_get_data_addr(param->img.img,
	&param->img.bits_per_pixel, &param->img.line_length, &param->img.endian);
}

static void		vectors_init(t_data *param)
{
	int		i;
	double	module;

	param->cam.O[0] = 0;
	param->cam.O[1] = 0;
	param->cam.O[2] = 0;
	param->cam.Vn[0] = 1;
	param->cam.Vn[1] = 0;
	param->cam.Vn[2] = 0;
	module = sqrt(pow(param->cam.Vn[0], 2) + pow(param->cam.Vn[1], 2) + pow(param->cam.Vn[2], 2));
	i = -1;
	while (++i < 3)
		param->cam.Vn[i] /= module;
	if (param->cam.Vn[0] >= 0 && param->cam.Vn[1] >= 0)
		param->cam.rot_z = asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] < 0 && param->cam.Vn[1] >= 0)
		param->cam.rot_z = M_PI - asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] < 0 && param->cam.Vn[1] < 0)
		param->cam.rot_z = M_PI + asin(param->cam.Vn[1]);
	else if (param->cam.Vn[0] >= 0 && param->cam.Vn[1] < 0)
		param->cam.rot_z = 2 * M_PI - asin(param->cam.Vn[1]);
	param->cam.rot_y = (param->cam.Vn[2] >= 0) ? asin(param->cam.Vn[2]) :
			2 * M_PI - asin(param->cam.Vn[2]);
	param->scr.fov = 90;
	param->scr.dist = (param->scr.x / 2) /
						tan((param->scr.fov / 2) * M_PI / 180);
}

static void		objs_init(t_data *param)
{
	param->sp = (t_sphere **)malloc(sizeof(t_sphere *));
	param->sp[0] = 0;
	param->l = (t_light **)malloc(sizeof(t_light *));
	param->l[0] = 0;
}

void	ft_init(t_data *param)
{
	double p[3];
	double p1[3];
	double p2[3];

	p[0] = 1000;
	p[1] = 0;
	p[2] = 0;
	p1[0] = 500;
	p1[1] = 500;
	p1[2] = 500;
	p2[0] = -500;
	p2[1] = -500;
	p2[2] = -500;

	mouse_init(param);
	screen_init(param);
	vectors_init(param);
	objs_init(param);
	param->sp = add_sp(param->sp, p, 500);
	param->sp = add_sp(param->sp, p1, 250);
	param->l = add_l(param->l, p2);
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
		param->crd.x = param->mou.x + x - param->scr.x / 2;
		param->crd.y = -(param->mou.y + y - param->scr.y / 2);
		if (param->crd.y > 249)
		{
			param->crd.y = 245;
			mlx_mouse_move(param->id, param->win_id, x, param->scr.y / 2 - param->crd.y);
		}
		else if (param->crd.y < -249)
		{
			param->crd.y = -245;
			mlx_mouse_move(param->id, param->win_id, x, param->scr.y / 2 - param->crd.y);
		}
		calculate_rotation(param);
		calculate_vectors(param);

		printf("X: %d, Y: %d\n", param->crd.x, param->crd.y);
		printf("Screen dist: %f\n", param->scr.dist);
		printf("Vn[x]: %f, Vn[y]: %f, Vn[z]: %f\n\n\n", param->cam.Vn[0], param->cam.Vn[1], param->cam.Vn[2]);
		printf("O = (%f, %f, %f)\n", param->cam.O[0], param->cam.O[1], param->cam.O[2]);
	}
	return (0);
}

int		button_pressed(int button, int x, int y, t_data *param)
{
	param->button = button;
	if (button == 1)
	{
		mlx_mouse_hide(param->id, param->win_id);
		mlx_mouse_move(param->id, param->win_id, param->scr.x / 2, param->scr.y / 2);
		param->crd.aux_x = x;
		param->crd.aux_y = y;
	}
	else if (button == 3)
	{
		vectors_init(param);
		mouse_init(param);
		calculate_rotation(param);
		calculate_vectors(param);
	}
	return (0);
}

int		button_released(int button, int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->mou.x += (x - param->scr.x / 2);
		param->mou.y += (y - param->scr.y / 2);
		mlx_mouse_move(param->id, param->win_id, param->crd.aux_x, param->crd.aux_y);
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
		param->cam.O[0] += param->cam.Vn[0] * 8;
		param->cam.O[1] += param->cam.Vn[1] * 8;
		param->cam.O[2] += param->cam.Vn[2] * 8;
	}
	else if (keycode == KEY_A)
	{
		param->cam.O[0] += param->cam.Vx[0] * -8;
		param->cam.O[1] += param->cam.Vx[1] * -8;
		param->cam.O[2] += param->cam.Vx[2] * -8;
	}
	else if (keycode == KEY_S)
	{
		param->cam.O[0] += param->cam.Vn[0] * -8;
		param->cam.O[1] += param->cam.Vn[1] * -8;
		param->cam.O[2] += param->cam.Vn[2] * -8;
	}
	else if (keycode == KEY_D)
	{
		param->cam.O[0] += param->cam.Vx[0] * 8;
		param->cam.O[1] += param->cam.Vx[1] * 8;
		param->cam.O[2] += param->cam.Vx[2] * 8;
	}
	else if (keycode == KEY_SPA)
		param->cam.O[2] += 3;
	else if (keycode == KEY_CTR)
		param->cam.O[2] += -3;
	calculate_rotation(param);
	calculate_vectors(param);
	//printf("key = %x\n", keycode);
	return (0);
}

int ft_loop(t_data *param)
{
	show_sp(param);
	//show_pov(param);
	//show_camera(param);
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
