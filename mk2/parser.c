/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/29 19:56:27 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void	set_param(t_data *param, char *line)
{
	set_settings(param, line);
	//set_obj(param, line);
}

static void		parse(t_data *param, char **argv)
{
	int		fd;
	char	*line;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		set_param(param, line);
		free(line);
	}
}

int		main(int argc, char **argv)
{
	t_data *param;

	param = (t_data *)malloc(sizeof(t_data));
	parse(param, argv);
	printf("resolution = %d x %d\n", param->scr.x, param->scr.y);
	printf("amb: %d, %d, %d\n", param->amb_l_rgb[0], param->amb_l_rgb[1], param->amb_l_rgb[2]);
	return (0);
}
