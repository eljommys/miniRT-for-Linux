/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/04 00:13:29 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void			parse(t_data *param, char **argv)
{
	int		fd;
	char	*line;
	int		error;
	fd = open(argv[1], O_RDONLY);
	error = 0;
	while (get_next_line(fd, &line) > 0)
	{
		error += def_settings(param, line);
		error += def_obj(param, line);
		error += def_elm(param, line);
		free(line);
	}
	close(fd);
	if (error)
	{
		write(1, "Invalid .rt file\n", 18);
		ft_exit(param);
	}
}
