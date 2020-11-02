/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:19:38 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/02 16:15:43 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void	ft_size(int i, char *size)
{

}

void	save_scr(t_data *param)
{
	int		fd;
	int		i;
	int		len;
	char	size[4];

	len = (param->scr.y * param->img.line_length +
			param->scr.x * (param->img.bits_per_pixel / 8));
	param->key = KEY_ENT;
	show_obj(param);
	fd = open("../screenshot.txt", O_WRONLY | O_CREAT);
	write(fd, "BM", 2);
	close(fd);
}
