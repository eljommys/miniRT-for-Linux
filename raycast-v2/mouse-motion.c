/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse-motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 09:25:07 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/13 13:02:47 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

//	gcc -o unit_test mouseMotion.c raycast.c ../minilibx-linux-master/*.a -L.. -lmlx -lXext -lX11 -lm -lbsd

static void		mouse_init(t_data *param)
{
	param->coord.x = 0;
	param->coord.y = 0;
	param->mouse.x = 0;
	param->mouse.y = 0;
	param->mouse.speed = 0.25;
}

static void		screen_init(t_data *param)
{
	param->screen.x = 1240;
	param->screen.y = 720;
	param->id = mlx_init();
	param->win_id = mlx_new_window(param->id, param->screen.x,
								param->screen.y, "hola");
	param->img = mlx_new_image(param->id, param->screen.x,
								param->screen.y);
	param->addr = mlx_get_data_addr(param->img, &param->bits_per_pixel,
								&param->line_length, &param->endian);
}

static void		vectors_init(t_data *param)
{
	int		i;
	double	module;

	param->Vn[0] = 1;
	param->Vn[1] = 0;
	param->Vn[2] = 0;
	module = sqrt(pow(param->Vn[0], 2) + pow(param->Vn[1], 2) +
			pow(param->Vn[2], 2));
	i = -1;
	while (++i < 3)
		param->Vn[i] /= module;
	if (param->Vn[0] >= 0 && param->Vn[1] >= 0)
		param->rot.z = asin(param->Vn[1]);
	else if (param->Vn[0] < 0 && param->Vn[1] >= 0)
		param->rot.z = M_PI - asin(param->Vn[1]);
	else if (param->Vn[0] < 0 && param->Vn[1] < 0)
		param->rot.z = M_PI + asin(param->Vn[1]);
	else if (param->Vn[0] >= 0 && param->Vn[1] < 0)
		param->rot.z = 2 * M_PI - asin(param->Vn[1]);
	param->rot.y = (param->Vn[2] >= 0) ? asin(param->Vn[2]) :
			2 * M_PI - asin(param->Vn[2]);
	param->screen.fov = 90;
	param->screen.dist = (param->screen.x / 2) /
						tan((param->screen.fov / 2) * M_PI / 180);
	param->rot.Vd[0] = 0;
	param->rot.Vd[1] = 0;
	param->rot.Vd[2] = 0;
}

void	ft_init(t_data *param)
{
	double p[3];

	p[0] = 1000;
	p[1] = 0;
	p[2] = 0;

	param->p = (double **)malloc(sizeof(double *));
	*param->p = 0;
	param->p_conv = (double **)malloc(sizeof(double *));
	*param->p_conv = 0;
	param->faces = (double ***)malloc(sizeof(double **));
	*param->faces = 0;
	create_cube(param, p, 500);
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
		param->coord.x = param->mouse.x + x - param->screen.x / 2;
		param->coord.y = -(param->mouse.y + y - param->screen.y / 2);
		if (param->coord.y > 249)
		{
			param->coord.y = 245;
			mlx_mouse_move(param->id, param->win_id, x, param->screen.y / 2
							- param->coord.y);
		}
		else if (param->coord.y < -249)
		{
			param->coord.y = -245;
			mlx_mouse_move(param->id, param->win_id, x, param->screen.y / 2
							- param->coord.y);
		}
		calculate_rotation(param);

		printf("X: %d, Y: %d\n", param->coord.x, param->coord.y);
		printf("Screen dist: %f\n", param->screen.dist);
		printf("Vn[x]: %f, Vn[y]: %f, Vn[z]: %f\n\n\n", param->Vn[0],
				param->Vn[1], param->Vn[2]);
	}
	return (0);
}

int		button_pressed(int button, int x, int y, t_data *param)
{
	param->button = button;
	if (button == 1)
	{
		mlx_mouse_hide(param->id, param->win_id);
		mlx_mouse_move(param->id, param->win_id, param->screen.x / 2,
						param->screen.y / 2);
		param->coord.aux_x = x;
		param->coord.aux_y = y;
	}
	else if (button == 3)
	{
		vectors_init(param);
		mouse_init(param);
		calculate_rotation(param);
	}
	return (0);
}

int		button_released(int button, int x, int y, t_data *param)
{
	if (param->button == 1)
	{
		param->mouse.x += (x - param->screen.x / 2);
		param->mouse.y += (y - param->screen.y / 2);
		mlx_mouse_move(param->id, param->win_id, param->coord.aux_x,
						param->coord.aux_y);
		mlx_mouse_show(param->id, param->win_id);
	}
	param->button = 0;
	return (0);
}

int		key_pressed(int keycode, t_data *param)
{
	printf("\nkey = %x\n", keycode);
	if (keycode == KEY_ESC)
		ft_exit(param->id);
	else if (keycode == KEY_W)
		param->rot.Vd[0] += -10;
	else if (keycode == KEY_A)
		param->rot.Vd[1] += -10;
	else if (keycode == KEY_S)
		param->rot.Vd[0] += 10;
	else if (keycode == KEY_D)
		param->rot.Vd[1] += 10;
	else if (keycode == KEY_SPA)
		param->rot.Vd[2] += -10;
	else if (keycode == KEY_CTR)
		param->rot.Vd[2] += 10;
	calculate_rotation(param);
	return (0);
}

int ft_loop(t_data *param)
{
	//printf("6\n");
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
