/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/30 12:29:59 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void 	print_scene(t_data *param)
{
	int n;
	int i;
	int j;

	n = ;
	i = -1;
	while (param->sp[++i])
	{
		printf("%d. sp: P(%.1f %.1f %.1f) d(%.1f) ")
	}
}

static void		parse(t_data *param, char **argv)
{
	int		fd;
	char	*line;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		def_settings(param, line);
		def_obj(param, line);
		free(line);
	}
}

int		main(int argc, char **argv)
{
	t_data *param;

	param = (t_data *)malloc(sizeof(t_data));
	ft_init(param);
	parse(param, argv);
	return (0);
}
