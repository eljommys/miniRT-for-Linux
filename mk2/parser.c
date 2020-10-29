/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:40:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/29 18:34:06 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

static void set_settings(t_data *param, char *line)
{
	int		i;
	int		j;
	int 	num_len;
	double	alpha;


	i = 0;
	alpha = -1;
	if (line[i] == 'R')
	{
		i++;
		while (line[i] == ' ')
			i++;
		param->scr.x = (int)ft_atoi(line + i);
		num_len = 0;
		while ('0' <= line[i + num_len] && line[i + num_len] <= '9')
			num_len++;
		i += num_len;
		while (line[i] != ' ')
			i++;
		param->scr.y = (int)ft_atoi(line + i);
	}
	else if (line[i] == 'A')
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
		{
			alpha = 1;
			i++;
		}
		else if (line[i] == '0')
		{
			i++;
			if (line[i] == '.')
			{
				i++;
				num_len = 0;
				while ('0' <= line[i + num_len] && line[i + num_len] <= '9')
					num_len++;
				alpha = (double)ft_atoi(line + i) / pow(10, num_len);
				i += num_len;
			}
			else
				alpha = 0;
		}
		while (line[i] == ' ')
			i++;
		j = -1;
		while (++j < 3)
		{
			param->amb_l_rgb[j] = ft_atoi(line + i) * alpha;
			num_len = 0;
			while ('0' <= line[i + num_len] && line[i + num_len] <= '9')
				num_len++;
			i += num_len + 1;;
		}
	}
}

static void	set_param(t_data *param, char *line)
{
	set_settings(param, line);
	//set_obj(param, line);
}

void		parse(t_data *param, char **argv)
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
