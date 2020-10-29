/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:24:10 by jserrano          #+#    #+#             */
/*   Updated: 2020/10/29 16:49:47 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# ifndef FD_SIZE
#  define FD_SIZE 4096
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"

//size_t		ft_strlen(char *str);
//char		*ft_strdup(char *s1);
//char		*ft_substr(char *s, unsigned int start, size_t len);
//char		*ft_strchr(char *s, int len);
//char		*ft_strjoin(char *s1, char *s2);
int			get_next_line(int fd, char **line);

#endif
