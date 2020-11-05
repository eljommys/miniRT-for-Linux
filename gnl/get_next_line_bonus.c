/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:23:36 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 14:23:41 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		make_str(char **str, char **line)
{
	int		len;
	char	*aux;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_substr(*str, 0, len);
		aux = ft_strdup(&((*str)[len + 1]));
		free(*str);
		*str = aux;
	}
	else
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		return (0);
	}
	return (1);
}

int		return_str(int fd, int num, char **str, char **line)
{
	if (num < 0)
		return (-1);
	else if (num == 0 && str[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (make_str(&str[fd], line));
}

int		get_next_line(int fd, char **line)
{
	static char	*str[FD_SIZE];
	char		*res;
	int			num;
	char		*aux;

	if (!(res = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, res, 0) < 0)
		return (-1);
	while ((num = read(fd, res, BUFFER_SIZE)) > 0)
	{
		res[num] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(res);
		else
		{
			aux = ft_strjoin(str[fd], res);
			free(str[fd]);
			str[fd] = aux;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	return (return_str(fd, num, str, line));
}
