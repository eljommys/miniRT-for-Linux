/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 12:39:50 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void			parse(t_data *param, char **argv)
{
	int		fd;
	char	*line;
	int		error;
	int		final[2];

	fd = open(argv[1], O_RDONLY);
	error = 0;
	final[0] = 1;
	final[1] = 0;
	while (final[0])
	{
		final[1] = (!get_next_line(fd, &line)) ? 1 : 0;
		final[0] -= final[1];
		error += def_settings(param, line);
		error += def_obj(param, line);
		error += def_elm(param, line);
		free(line);
	}
	close(fd);
	if (error)
	{
		write(1, "Error\n", 7);
		write(1, "Invalid .rt file\n", 18);
		ft_exit(param);
	}
}
