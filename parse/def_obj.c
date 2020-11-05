/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:12:24 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 23:53:02 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

int		def_obj(t_data *param, char *line)
{
	int error;

	error = 0;
	if (!ft_memcmp(line, "sp", 2))
		error += def_sp(param, line);
	else if (!ft_memcmp(line, "pl", 2))
		error += def_pl(param, line);
	else if (!ft_memcmp(line, "cy", 2))
		error += def_cy(param, line);
	else if (!ft_memcmp(line, "sq", 2))
		error += def_sq(param, line);
	else if (!ft_memcmp(line, "tr", 2))
		error += def_tr(param, line);
	else if (!ft_memcmp(line, "bx", 2))
		error += def_bx(param, line);
	if (error)
		return (1);
	return (0);
}
