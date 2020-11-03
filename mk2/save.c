/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:19:38 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 12:03:04 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void	dec_hex_endian(int len, unsigned char *size)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		size[i] = len % 256;
		len /= 256;
	}
}

static void	write_header(t_data *param, int fd)
{
	unsigned char	bytes[4];
	int 			len;

	len = param->scr.y * param->img.line_length +
			param->scr.x * (param->img.bits_per_pixel / 8);
	write(fd, "BM", 2);
	dec_hex_endian(len + 54, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\66\0\0\0\50\0\0\0", 12);
	dec_hex_endian(param->scr.x, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(param->scr.y, bytes);
	write(fd, bytes, 4);
	write(fd, "\1\0\40\0\0\0\0\0", 8);
	dec_hex_endian(0, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(param->scr.x, bytes);
	write(fd, bytes, 4);
	dec_hex_endian(param->scr.y, bytes);
	write(fd, bytes, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
}

void		save_scr(t_data *param)
{
	int				fd;
	int				i;

	param->key = KEY_ENT;
	show_obj(param);
	fd = open("../screenshot.bmp", O_WRONLY | O_CREAT);
	write_header(param, fd);
	i = param->scr.y;
	while (--i >= 0)
		write(fd, param->img.addr + i * param->img.line_length,
			param->scr.x * (param->img.bits_per_pixel / 8));
	close(fd);
}
