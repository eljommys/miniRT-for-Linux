/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:25:31 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/28 14:25:31 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char		*ft_strdup(char *s1)
{
	char	*s2;
	int		i;
	int		size;

	size = ft_strlen(s1);
	i = 0;
	s2 = (char*)malloc(sizeof(char) * size + 1);
	if (s2 == NULL)
	{
		return (s2);
	}
	while (i <= size)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
	{
		return (NULL);
	}
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	substr = (char*)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (substr);
	while (s[i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char		*ft_strchr(char *s, int len)
{
	while (*s)
	{
		if (*s == len)
		{
			return ((char*)s);
		}
		s++;
	}
	if (len == '\0')
	{
		return ((char*)s);
	}
	return (NULL);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (join);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
