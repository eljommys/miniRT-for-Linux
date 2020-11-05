/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:53:01 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/05 14:53:03 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void	ft_hooks(t_data *param)
{
	mlx_hook(param->win_id, KEY_PR, MK_KEY_PR, key_pressed, param);
	mlx_hook(param->win_id, BUT_PR, MK_BUT_PR, button_pressed, param);
	mlx_hook(param->win_id, BUT_RE, MK_BUT_RE, button_released, param);
	mlx_hook(param->win_id, MOT_NT, MK_PTR_MO, get_pos, param);
	mlx_hook(param->win_id, CLI_MG, CL_CLOSE, ft_exit, param);
	mlx_loop_hook(param->id, show_obj, param);
}

static void	main_ifs(t_data *param, int argc, char **argv)
{
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

int			main(int argc, char **argv)
{
	t_data	*param;
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
		ft_hooks(param);
		main_ifs(param, argc, argv);
	}
	else
		write(1, "Wrong number of arguments!\n", 28);
	return (0);
}