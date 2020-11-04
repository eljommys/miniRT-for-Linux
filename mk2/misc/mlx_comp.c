/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_comp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:57:37 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 14:56:39 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

static void	free_elm(t_data *param)
{
	int	i;

	i = -1;
	while (param->l[++i])
		free(param->l[i]);
	free(param->l);
	i = -1;
	while (param->c[++i])
		free(param->c[i]);
	free(param->c);
}

static void	free_obj_1(t_data *param)
{
	int i;

	i = -1;
	while (param->sp[i])
		free(param->sp[i]);
	free(param->sp);
	i = -1;
	while (param->pl[++i])
		free(param->pl[i]);
	free(param->pl);
	i = -1;
	while (param->cy[++i])
		free(param->cy[i]);
	free(param->cy);
}

static void	free_obj_2(t_data *param)
{
	int i;

	i = -1;
	while (param->sq[++i])
		free(param->sq[i]);
	free(param->sq);
	i = -1;
	while (param->bx[++i])
		free(param->bx[i]);
	free(param->bx);
	i = -1;
	while (param->tr[++i])
		free(param->tr[i]);
	free(param->tr);
}

int			ft_exit(t_data *param)
{
	free(param->id);
	free(param->win_id);
	free(param->img.img);
	free_elm(param);
	free_obj_1(param);
	free_obj_2(param);
	free(param);
	exit(0);
	return (0);
}

void		my_mlx_pixel_put(t_data *param, int x, int y, int color)
{
	char	*dst;

	dst = param->img.addr + (y * param->img.line_length + x *
			(param->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
