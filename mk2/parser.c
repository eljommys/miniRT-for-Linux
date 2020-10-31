/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/31 12:12:01 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

void			parse(t_data *param, char **argv)
{
	int		fd;
	char	*line;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		def_settings(param, line);
		def_obj(param, line);
		def_elm(param, line);
		free(line);
	}
	close(fd);
}
