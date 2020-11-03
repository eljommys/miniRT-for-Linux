/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:19:38 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 02:19:04 by jserrano         ###   ########.fr       */
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

void	save_scr(t_data *param)
{
	int				fd;
	int				i;
	int				len;
	unsigned char	bytes[4];

	len = (param->scr.y * param->img.line_length +
			param->scr.x * (param->img.bits_per_pixel / 8));
	param->key = KEY_ENT;
	show_obj(param);
	fd = open("../screenshot.bmp", O_WRONLY | O_CREAT);
	write(fd, "BM", 2);
	dec_hex_endian(len + 54, bytes);
	write(fd, bytes, 4);	//size of file
	write(fd, "\0\0\0\0", 4);
	write(fd, "\66\0\0\0", 4);	//starting at byte 54 in octal 66
	write(fd, "\50\0\0\0", 4);	//size of header 40 in octal 50
	dec_hex_endian(param->scr.x, bytes);
	write(fd, bytes, 4);	//with
	dec_hex_endian(param->scr.y, bytes);
	write(fd, bytes, 4);	//height
	write(fd, "\1\0", 2);	//color planes
	write(fd, "\40\0", 2);	//bits perpixel 32 in octal 40
	write(fd, "\0\0\0\0", 4);	//compression = BI_RGB -> 0
	dec_hex_endian(0, bytes);
	write(fd, bytes, 4);	//image size. 0 for BI_RGB
	dec_hex_endian(param->scr.x, bytes);
	write(fd, bytes, 4);	//horizontal resolution
	dec_hex_endian(param->scr.y, bytes);
	write(fd, bytes, 4);	//vertical resolution
	write(fd, "\0\0\0\0", 4);	//number of colors default 0
	write(fd, "\0\0\0\0", 4);	//important colors all 0
	write(fd, param->img.addr, len);	//image array. se voltea verticalmente
	close(fd);
}
