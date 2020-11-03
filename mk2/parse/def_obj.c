/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:12:24 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/03 15:50:22 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raymarching.h"

void 		def_obj(t_data *param, char *line)
{
	if (!ft_memcmp(line, "sp", 2))
		def_sp(param, line);
	else if (!ft_memcmp(line, "pl", 2))
		def_pl(param, line);
	else if (!ft_memcmp(line, "cy", 2))
		def_cy(param, line);
	else if (!ft_memcmp(line, "sq", 2))
		def_sq(param, line);
	else if (!ft_memcmp(line, "tr", 2))
		def_tr(param, line);
	else if (!ft_memcmp(line, "bx", 2))
		def_bx(param, line);
}
